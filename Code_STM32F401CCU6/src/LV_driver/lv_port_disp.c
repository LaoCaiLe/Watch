#if 1
#include "lv_port_disp.h"
#include "lcd.h"
#include "mcu_type.h"
#include "lcd_init.h"

static lv_disp_drv_t * disp_drv_p;
#define COLOR_BUF_SIZE (LV_HOR_RES_MAX*LV_VER_RES_MAX/ 10)
//���䵽�ⲿ 1MB sram ������ʼ��
static lv_color_t color_buf1[COLOR_BUF_SIZE];
static lv_color_t color_buf2[COLOR_BUF_SIZE];

static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);



static void disp_spi_dma_send(void* buf, uint32_t size)
{
    DMA_Cmd(DMA2_Stream3, DISABLE);
    DMA2_Stream3->M0AR = (uint32_t)buf;
    DMA2_Stream3->NDTR = size;
    DMA_Cmd(DMA2_Stream3, ENABLE);
    
//    while(DMA_GetFlagStatus(DMA2_Stream3,DMA_FLAG_TCIF3) == RESET){} //�ȴ�DMA�������
//    DMA_ClearFlag(DMA2_Stream3, DMA_FLAG_TCIF3); // �����־
}

//��ָ���������ʾ����������д�뵽��Ļ��,�����ʹ�� DMA ����������Ӳ��������
//�ں�̨ȥ�������������������֮��,�����õ��� lv_disp_flush_ready()
static void disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    disp_drv_p = disp_drv;
    
    //screen.drawFastRGBBitmap(area->x1, area->y1, (uint16_t*)color_p, (area->x2 - area->x1 + 1), (area->y2 - area->y1 + 1));
    
    int16_t w = (area->x2 - area->x1 + 1);
    int16_t h = (area->y2 - area->y1 + 1);
    uint32_t size = w * h * sizeof(lv_color_t);
    
    /*����ˢ������*/
    LCD_Address_Set(area->x1, area->y1, area->x2, area->y2);
    

    /*Ƭѡ������ģʽ*/
    // digitalWrite_LOW(PA4);
    LCD_CS_Clr();
    LCD_DC_Set();
    // digitalWrite_HIGH(PB1);

    /*DMA��������*/
    disp_spi_dma_send(color_p, size);
    
//    digitalWrite_HIGH(TFT_CS_Pin);
//    lv_disp_flush_ready(disp_drv_p);/* tell lvgl that flushing is done */
    // u16 *color = (u16 *)color_p;
    // LCD_COLOR_FILL(area->x1, area->y1, area->x2, area->y2, (u16*)color_p); // TODO
    // LCD_ShowPicture(area->x1, area->y1, area->x2, area->y2, (u16*)color_p);
    //    DMA_Fill_Color(area->x1,area->y1,area->x2,area->y2,(u16*)color_p);
    // lv_disp_flush_ready(disp_drv);//������õ���,֪ͨ lvgl �����Ѿ� flushing ���������
}

void DMA2_Stream3_IRQHandler(void)
{
    /*DMA��������ж�*/
    if(DMA_GetITStatus(DMA2_Stream3, DMA_IT_TCIF3) != RESET)
    {
        // digitalWrite_HIGH(TFT_CS_Pin);
        LCD_CS_Set();
        lv_disp_flush_ready(disp_drv_p); /* tell lvgl that flushing is done */
        DMA_ClearITPendingBit(DMA2_Stream3, DMA_IT_TCIF3);
    }
}


/**
  * @brief  DMA��ʼ��
  * @param  ��
  * @retval ��
  */
static void disp_spi_dma_init()
{
    DMA_InitTypeDef  DMA_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE); //DMA2ʱ��ʹ��
    DMA_DeInit(DMA2_Stream3);
    while(DMA_GetCmdStatus(DMA2_Stream3) != DISABLE) {} //�ȴ�DMA������

    /* ���� DMA Stream */
    DMA_InitStructure.DMA_Channel = DMA_Channel_3;  //ͨ��ѡ��
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) & (SPI1->DR); //DMA�����ַ
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)color_buf1;//DMA �洢��0��ַ
    DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;//�洢��������ģʽ
    DMA_InitStructure.DMA_BufferSize = sizeof(color_buf1);//���ݴ�����
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//���������ģʽ
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�洢������ģʽ
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//�������ݳ���:8λ
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//�洢�����ݳ���:8λ
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;// ʹ����ͨģʽ
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;//�е����ȼ�
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//�洢��ͻ�����δ���
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//����ͻ�����δ���
    DMA_Init(DMA2_Stream3, &DMA_InitStructure);//��ʼ��DMA Stream
        
    SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE); // SPI1ʹ��DMA����
    
    NVIC_EnableIRQ(DMA2_Stream3_IRQn);
    DMA_ITConfig(DMA2_Stream3, DMA_IT_TC, ENABLE);
}

/**
  * @brief  ��Ļ��ʼ��
  * @param  ��
  * @retval ��
  */
void lv_port_disp_init(void)
{
    disp_spi_dma_init();

    static lv_disp_buf_t disp_buf;
    //color_buf = (lv_color_t *)0X68000000;//��ʾ��������ʼ��
    lv_disp_buf_init(&disp_buf, color_buf1, color_buf2, COLOR_BUF_SIZE);
    
    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);

    //ע����ʾ�����ص�
    disp_drv.flush_cb = disp_flush;
    
    //ע����ʾ������
    disp_drv.buffer = &disp_buf;
    
    //ע����ʾ������ lvgl ��
    lv_disp_drv_register(&disp_drv);
}
// void lv_port_disp_init()
// {
//     // disp_spi_dma_init();

//     static lv_disp_buf_t disp_buf;
//     lv_disp_buf_init(&disp_buf, color_buf1, color_buf2, COLOR_BUF_SIZE);

//     /*Initialize the display*/
//     lv_disp_drv_t disp_drv;
//     lv_disp_drv_init(&disp_drv);
//     disp_drv.flush_cb = disp_flush;
//     disp_drv.buffer = &disp_buf;
//     lv_disp_drv_register(&disp_drv);
// }

#else /* Enable this file at the top */
/* This dummy typedef exists purely to silence -Wpedantic. */
typedef int keep_pedantic_happy;
#endif