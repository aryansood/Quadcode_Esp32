#include "Arduino.h"
#include "driver/rmt.h"

#define RMT_TX_CHANNEL_1 RMT_CHANNEL_0
#define RMT_TX_CHANNEL_2 RMT_CHANNEL_1
#define RMT_TX_CHANNEL_3 RMT_CHANNEL_2
#define RMT_TX_CHANNEL_4 RMT_CHANNEL_3

#define RMT_TX_GPIO_NUM_1 GPIO_NUM_16
#define RMT_TX_GPIO_NUM_2 GPIO_NUM_17
#define RMT_TX_GPIO_NUM_3 GPIO_NUM_18
#define RMT_TX_GPIO_NUM_4 GPIO_NUM_19


enum DSHOT_VALUES {DSHOT_150, DSHOT_300, DSHOT_600};

struct DSHOT_MODE
{
    /*
    Selection Mode is in the following way:
    index 0 select 150
    index 1 select 300
    index 2 select 600
    */
    uint32_t duration_total[3] = {107,53,27};
    uint32_t duration_0[3] = {40,20,10};
    uint32_t duration_1[3] = {80,40,20};

    /*Dshot600:
    10 625ns
    
    */
};

void DSHOT_SETUP_DSHOT(rmt_channel_t Channel, gpio_num_t Gpio_num)
{
    rmt_config_t rmt_tx;
    rmt_tx.channel = Channel;
    rmt_tx.gpio_num = Gpio_num;
    rmt_tx.mem_block_num = 1;
    rmt_tx.clk_div = 5;
    rmt_tx.tx_config.loop_en = false;
    rmt_tx.tx_config.carrier_en = false;
    rmt_tx.tx_config.idle_output_en = true;
    rmt_tx.tx_config.idle_level = RMT_IDLE_LEVEL_LOW;
    rmt_tx.rmt_mode = RMT_MODE_TX;

    rmt_config(&rmt_tx);
    rmt_driver_install(rmt_tx.channel, 0, 0);   
}

void DSHOT_MOTOR_SETUP()
{
    DSHOT_SETUP_DSHOT(RMT_TX_CHANNEL_1,RMT_TX_GPIO_NUM_1);
    DSHOT_SETUP_DSHOT(RMT_TX_CHANNEL_2,RMT_TX_GPIO_NUM_2);
    DSHOT_SETUP_DSHOT(RMT_TX_CHANNEL_3,RMT_TX_GPIO_NUM_3);
    DSHOT_SETUP_DSHOT(RMT_TX_CHANNEL_4,RMT_TX_GPIO_NUM_4);
}

void DSHOT_SEND_COMMAND(uint16_t frame, DSHOT_VALUES mode, rmt_channel_t motor_channel)
{
    struct DSHOT_MODE MODE;
    rmt_item32_t Dshot_frame[16];
    for(int i = 0;i<16;i++)
    {
        if((frame>>(15-i) & 1) == 1)
        {
            Dshot_frame[i].level0 = 1; 
            Dshot_frame[i].duration0 = MODE.duration_1[mode];
            Dshot_frame[i].level1 = 0;   
            Dshot_frame[i].duration1 = MODE.duration_total[mode]-MODE.duration_1[mode];
        }
        else
        {
            Dshot_frame[i].level0 = 1; 
            Dshot_frame[i].duration0 = MODE.duration_0[mode];
            Dshot_frame[i].level1 = 0;   
            Dshot_frame[i].duration1 = MODE.duration_total[mode]-MODE.duration_0[mode];
        }
    }

    rmt_write_items(motor_channel, Dshot_frame, 16, true);
}

void DSHOT_MOTOR_INITIALIZATION()
{
    for(int i = 0;i<1000;i++)
    {
        DSHOT_SEND_COMMAND(0,DSHOT_300,RMT_TX_CHANNEL_1);
        DSHOT_SEND_COMMAND(0,DSHOT_300,RMT_TX_CHANNEL_2);
        DSHOT_SEND_COMMAND(0,DSHOT_300,RMT_TX_CHANNEL_3);
        DSHOT_SEND_COMMAND(0,DSHOT_300,RMT_TX_CHANNEL_4);
        delay(10);
    }
}

uint16_t DSHOT_ADD_CHECKSUM(uint16_t frame_w_c)
{
    uint16_t checksum = 0;
    frame_w_c = frame_w_c<<1;
    checksum  = (frame_w_c ^ (frame_w_c >> 4) ^ (frame_w_c >> 8)) & 0x0F;
    frame_w_c = frame_w_c<<4;
    frame_w_c = frame_w_c+checksum;
    return frame_w_c;
}

void DSHOT_REVERSE_MOTOR_SPIN()
{
    uint16_t clockwise = 7;
    uint16_t counter_clockwise = 8;
    clockwise = DSHOT_ADD_CHECKSUM(clockwise);
    counter_clockwise = DSHOT_ADD_CHECKSUM(counter_clockwise);
    //DSHOT_SEND_COMMAND(0,DSHOT_300,RMT_TX_CHANNEL_1);
    //DSHOT_SEND_COMMAND(0,DSHOT_300,RMT_TX_CHANNEL_2);
    //DSHOT_SEND_COMMAND(0,DSHOT_300,RMT_TX_CHANNEL_3);
    //DSHOT_SEND_COMMAND(0,DSHOT_300,RMT_TX_CHANNEL_4);
    DSHOT_SEND_COMMAND(clockwise,DSHOT_300,RMT_TX_CHANNEL_1);
    DSHOT_SEND_COMMAND(clockwise,DSHOT_300,RMT_TX_CHANNEL_2);
    DSHOT_SEND_COMMAND(clockwise,DSHOT_300,RMT_TX_CHANNEL_3);
    DSHOT_SEND_COMMAND(clockwise,DSHOT_300,RMT_TX_CHANNEL_4);
}

void DSHOT_MOTOR_SEND_THROTTLE(int motor_1, int motor_2, int motor_3, int motor_4)
{
    int motor_throttle[4];
    motor_throttle[0] = motor_1;
    motor_throttle[1] = motor_2;
    motor_throttle[2] = motor_3;
    motor_throttle[3] = motor_4;
    uint16_t data_tx[4];
    for(int i = 0;i<4;i++)
    {
        if(motor_throttle[i]<0) motor_throttle[i] = 0;
        else if(motor_throttle[i] > 100) motor_throttle[i] = 100;
        if(motor_throttle[i] == 0)
        {
            data_tx[i] = 0;
        }
        else
        {
            data_tx[i] = 48+(motor_throttle[i]*1999)/100;
        }
        data_tx[i] = DSHOT_ADD_CHECKSUM(data_tx[i]);
    }
    DSHOT_SEND_COMMAND(data_tx[0],DSHOT_300,RMT_TX_CHANNEL_1);
    DSHOT_SEND_COMMAND(data_tx[1],DSHOT_300,RMT_TX_CHANNEL_2);
    DSHOT_SEND_COMMAND(data_tx[2],DSHOT_300,RMT_TX_CHANNEL_3);
    DSHOT_SEND_COMMAND(data_tx[3],DSHOT_300,RMT_TX_CHANNEL_4);
}