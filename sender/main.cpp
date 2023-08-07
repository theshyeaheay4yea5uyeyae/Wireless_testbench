#include "RF24.h"
#include "mbed.h"
#include "ThisThread.h"

// Pin configuration for the first radio (replace with the actual pins you're using)
PinName mosi = PA_12;
PinName miso = PA_11;
PinName sck = PA_1;
PinName ce = D5;
PinName csn = D6;

// Create RF24 object
RF24 radio(mosi, miso, sck, ce, csn);

// Define the address for the pipe
const uint8_t address[6] = "00001";

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
    radio.openWritingPipe(address);

    uint8_t Channel = radio.getChannel();
    printf("Channel: %d\n", Channel);
    radio.setChannel(100);

    // Start listening
    radio.stopListening();

    printf("Data rate: %d\n", radio.getDataRate());

    int count = 0; // Initialize counter
    Timer timer;   // Create a Timer object

    while (true) {  // main loop
        

        // Format the message to include the counter
        char message[8];  // Make sure this is large enough to hold your entire message
        snprintf(message, sizeof(message), "C%d", count);
        
    

        // Check if the message was sent
        timer.start();  // Start the timer

        // Send the message
        bool ok = radio.write(&message, sizeof(message));

        
        timer.stop();  // Stop the timer

        if (ok) {
            printf("Message sent: %s\n", message);
        } else {
            printf("Failed to send message\n");
        }

        printf("Time taken for loop: %llu us\n", timer.elapsed_time().count());
        printf("Time taken for loop: %llu ms\n", timer.elapsed_time().count() / 1000);
        timer.reset();  // Reset the timer for the next loop

        // Increment the counter
        count++;

        // Delay for a bit
        ThisThread::sleep_for(1000);  // delay in ms

        

        
        
        uint8_t PayloadSize = radio.getPayloadSize();
        printf("PayloadSize: %d\n", PayloadSize);


    }
}
