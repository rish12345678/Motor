<img width="1443" height="723" alt="Screenshot 2026-07-06 at 4 38 49 PM" src="https://github.com/user-attachments/assets/07e1fef4-ecf4-41c4-9064-fb66adca717a" />
Fig 1.1: Initial waveform Sending Dummy Byte (0x24) Over MOSI Line
Issue to fix: Right now I am using a for loop to handle delays between byte transmissions, delay is too large, implement an accurate time sensitive way to regulate delays

<img width="1251" height="636" alt="Screenshot 2026-07-06 at 5 33 46 PM" src="https://github.com/user-attachments/assets/32ed1b3a-a7dc-4b31-9fa9-74bedad9e916" />
Fig 1.2: Scaled waveform sending 0x84 Over MOSI Line
Issue to fix: The CS line is going high before a single clock cycle of data is sent, make CS stay low until all eight bits are sent over

<img width="1248" height="634" alt="Screenshot 2026-07-07 at 3 37 13 AM" src="https://github.com/user-attachments/assets/136f1f80-bf3a-4b92-b191-7957a1523f52" />
Fig 1.3: Complete validation of loopback test to ensure MISO line works appropriately, and we can echo bytes back

<img width="1246" height="632" alt="Screenshot 2026-07-07 at 2 51 12 PM" src="https://github.com/user-attachments/assets/b2e70168-0dd6-426b-a762-6d1c9785ee67" />
Fig 1.4: Set polling wall to check that RX FIFO receives byte and seperate one to ensure Shift Register BSY flag set to zero, so it is done with transmission + cleanup, then raise CS high only AFTER all bits have been transceived

#### Now all pins are functioning correctly.  The polling driver for SPI1 is complete.  Next, interrupts....
