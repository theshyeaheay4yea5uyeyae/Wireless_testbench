#include "RF24.h"
#include "mbed.h"
#include "ThisThread.h"

// Pin configuration for the second radio (replace with the actual pins you're using)
PinName mosi = PB_5;
PinName miso = PB_4;
PinName sck = PB_3;
PinName ce = A3;
PinName csn = A2;

// Create RF24 object
RF24 radio(mosi, miso, sck, ce, csn);

// Define the address for the pipe
const uint8_t address[6] = "00001";

Timer timer;

int main() {
    printf("start\n");

    // Initialize the RF24 module
    if (radio.begin()) {
        printf("Radio is responding\n");
    } else {
        printf("Failed to initialize radio\n");
    }

    // Set the Data Rate to 1Mbps
    radio.setDataRate(RF24_1MBPS);

    radio.setPayloadSize(4);

    // Open the pipe for communication
    radio.openReadingPipe(0, address);  // use pipe number 1 instead of 0


    uint8_t Channel = radio.getChannel();
    printf("Channel: %d\n", Channel);
    radio.setChannel(100);

    // Start listening
    radio.startListening();

    printf("Data rate: %d\n", radio.getDataRate());

    while (true) {  // main loop
        char receivePayload[8] = "";
        // Check if there is data ready
        timer.start();  // Start the timer
        if (radio.available()) {
            // Declare a buffer to put the data in
            

            // Read the data
            radio.read(receivePayload, sizeof(receivePayload));

        }
        timer.stop();  // Stop the timer
            printf("Time taken for loop: %llu us\n", timer.elapsed_time().count());
            printf("Time taken for loop: %llu ms\n", timer.elapsed_time().count() / 1000);
            timer.reset();  // Reset the timer for the next loop


        // Print out the received payload
            printf("Received message: %s\n", receivePayload);


        uint8_t Channel = radio.getChannel();
        printf("Channel: %d\n", Channel);

        ThisThread::sleep_for(200);


    }
}
