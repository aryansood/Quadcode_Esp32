#include "Arduino.h"
#include "driver/rmt.h"
#include "Motors_Control/Dshot.h"

void setup()
{
    DSHOT_MOTOR_SETUP();
    //DSHOT_MOTOR_INITIALIZATION();
    DSHOT_MOTOR_INITIALIZATION();
    for(int i = 0;i<100;i++)
    {
        DSHOT_MOTOR_SEND_THROTTLE(10,20,30,40);
        delay(100);
    }
    DSHOT_MOTOR_SEND_THROTTLE(10,20,30,40);
    DSHOT_MOTOR_SEND_THROTTLE(10,20,30,40);
    delay(1000);
}

void loop()
{
    //DSHOT_REVERSE_MOTOR_SPIN();
    //delay(100);
    DSHOT_MOTOR_SEND_THROTTLE(10,20,30,40);
    int a = 0;
    a++;
    if(a>100) a = 0;
}

/*
#define RMT_TX_CHANNEL RMT_CHANNEL_0
#define RMT_TX_GPIO_NUM GPIO_NUM_19


void setupRMT() {
    rmt_config_t rmt_tx;
    rmt_tx.channel = RMT_TX_CHANNEL;
    rmt_tx.gpio_num = GPIO_NUM_19;
    rmt_tx.mem_block_num = 1;
    rmt_tx.clk_div = 5; //5//20 2 4
    rmt_tx.tx_config.loop_en = false;
    rmt_tx.tx_config.carrier_en = false;
    rmt_tx.tx_config.idle_output_en = true;
    rmt_tx.tx_config.idle_level = RMT_IDLE_LEVEL_LOW;
    rmt_tx.rmt_mode = RMT_MODE_TX;

    rmt_config(&rmt_tx);
    rmt_driver_install(rmt_tx.channel, 0, 0);
}

void sendSingleHigh() {
    rmt_item32_t item;
    item.level0 = 1;
    item.duration0 = 4;  // 2ms
    item.level1 = 0;
    item.duration1 = 4;  // 100ms
    rmt_write_items(RMT_TX_CHANNEL, &item, 1, true);
    delay(500);  // 500ms delay before sending next pulse
}


void sendPulseSequence() {
    rmt_item32_t items[6];
    
    for (int i = 0; i < 6; i++) {
        if (i == 0 || i == 1 || i == 5) {
            items[i].level0 = 1; 
            items[i].duration0 = 12;//10;  // 100ms
            items[i].level1 = 0;   
            items[i].duration1 = 10;//16;  // 100ms
        } else {
            items[i].level0 = 1;   
            items[i].duration0 = 12; //10;  // 100ms
            items[i].level1 = 0;   
            items[i].duration1 = 10;//16;  // 100ms
        }
    }

    rmt_write_items(RMT_TX_CHANNEL, items, 6, true);
    delay(10);  // 1s delay before sending the next sequence
}


void setup() {
    setupRMT();
}

void loop() {
   sendPulseSequence();
}
*/