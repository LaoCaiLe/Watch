#if 1
#include "lv_port_disp.h"
#include "lcd.h"
#include "mcu_type.h"
#include "lcd_init.h"

static lv_disp_drv_t * disp_drv_p;
#define COLOR_BUF_SIZE (LV_HOR_RES_MAX*LV_VER_RES_MAX/ 10)
//分配到外部 1MB sram 的最起始处
static lv_color_t color_buf1[COLOR_BUF_SIZE];
static lv_color_t color_buf2[COLOR_BUF_SIZE];

static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);



static void disp_spi_dma_send(void* buf, uint32_t size)
{
    DMA_Cmd(DMA2_Stream3, DISABLE);
    DMA2_Stream3->M0AR = (uint32_t)buf;
    DMA2_Stream3->NDTR = size;
    DMA_Cmd(DMA2_Stream3, ENABLE);
    
//    while(DMA_GetFlagStatus(DMA2_Stream3,DMA_FLAG_TCIF3) == RESET){} //等待DMA传输完成
//    DMA_ClearFlag(DMA2_Stream3, DMA_FLAG_TCIF3); // 清除标志
}

//把指定区域的显示缓冲区内容写入到屏幕上,你可以使用 DMA 或者其他的硬件加速器
//在后台去完成这个操作但是在完成之后,你必须得调用 lv_disp_flush_ready()
static void disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    disp_drv_p = disp_drv;
    
    //screen.drawFastRGBBitmap(area->x1, area->y1, (uint16_t*)color_p, (area->x2 - area->x1 + 1), (area->y2 - area->y1 + 1));
    
    int16_t w = (area->x2 - area->x1 + 1);
    int16_t h = (area->y2 - area->y1 + 1);
    uint32_t size = w * h * sizeof(lv_color_t);
    
    /*设置刷新区域*/
    LCD_Address_Set(area->x1, area->y1, area->x2, area->y2);
    

    /*片选，数据模式*/
    // digitalWrite_LOW(PA4);
    LCD_CS_Clr();
    LCD_DC_Set();
    // digitalWrite_HIGH(PB1);

    /*DMA发送请求*/
    disp_spi_dma_send(color_p, size);
    
//    digitalWrite_HIGH(TFT_CS_Pin);
//    lv_disp_flush_ready(disp_drv_p);/* tell lvgl that flushing is done */
    // u16 *color = (u16 *)color_p;
    // LCD_COLOR_FILL(area->x1, area->y1, area->x2, area->y2, (u16*)color_p); // TODO
    // LCD_ShowPicture(area->x1, area->y1, area->x2, area->y2, (u16*)color_p);
    //    DMA_Fill_Color(area->x1,area->y1,area->x2,area->y2,(u16*)color_p);
    // lv_disp_flush_ready(disp_drv);//最后必须得调用,通知 lvgl 库你已经 flushing 拷贝完成了
}

void DMA2_Stream3_IRQHandler(void)
{
    /*DMA发送完成中断*/
    if(DMA_GetITStatus(DMA2_Stream3, DMA_IT_TCIF3) != RESET)
    {
        // digitalWrite_HIGH(TFT_CS_Pin);
        LCD_CS_Set();
        lv_disp_flush_ready(disp_drv_p); /* tell lvgl that flushing is done */
        DMA_ClearITPendingBit(DMA2_Stream3, DMA_IT_TCIF3);
    }
}


/**
  * @brief  DMA初始化
  * @param  无
  * @retval 无
  */
static void disp_spi_dma_init()
{
    DMA_InitTypeDef  DMA_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE); //DMA2时钟使能
    DMA_DeInit(DMA2_Stream3);
    while(DMA_GetCmdStatus(DMA2_Stream3) != DISABLE) {} //等待DMA可配置

    /* 配置 DMA Stream */
    DMA_InitStructure.DMA_Channel = DMA_Channel_3;  //通道选择
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) & (SPI1->DR); //DMA外设地址
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)color_buf1;//DMA 存储器0地址
    DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;//存储器到外设模式
    DMA_InitStructure.DMA_BufferSize = sizeof(color_buf1);//数据传输量
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//外设非增量模式
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//存储器增量模式
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//外设数据长度:8位
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//存储器数据长度:8位
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;// 使用普通模式
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;//中等优先级
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//存储器突发单次传输
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//外设突发单次传输
    DMA_Init(DMA2_Stream3, &DMA_InitStructure);//初始化DMA Stream
        
    SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE); // SPI1使能DMA发送
    
    NVIC_EnableIRQ(DMA2_Stream3_IRQn);
    DMA_ITConfig(DMA2_Stream3, DMA_IT_TC, ENABLE);
}

/**
  * @brief  屏幕初始化
  * @param  无
  * @retval 无
  */
void lv_port_disp_init(void)
{
    disp_spi_dma_init();

    static lv_disp_buf_t disp_buf;
    //color_buf = (lv_color_t *)0X68000000;//显示缓冲区初始化
    lv_disp_buf_init(&disp_buf, color_buf1, color_buf2, COLOR_BUF_SIZE);
    
    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);

    //注册显示驱动回调
    disp_drv.flush_cb = disp_flush;
    
    //注册显示缓冲区
    disp_drv.buffer = &disp_buf;
    
    //注册显示驱动到 lvgl 中
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