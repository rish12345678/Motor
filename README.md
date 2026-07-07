<img width="1443" height="723" alt="Screenshot 2026-07-06 at 4 38 49 PM" src="https://github.com/user-attachments/assets/07e1fef4-ecf4-41c4-9064-fb66adca717a" />
Fig 1.1: Initial waveform Sending Dummy Byte (0x24) Over MOSI Line
Issue to fix: Right now I am using a for loop to handle delays between byte transmissions, delay is too large, implement an accurate time sensitive way to regulate delays

<img width="1251" height="636" alt="Screenshot 2026-07-06 at 5 33 46 PM" src="https://github.com/user-attachments/assets/32ed1b3a-a7dc-4b31-9fa9-74bedad9e916" />
Fig 1.2: Scaled waveform sending 0x84 Over MOSI Line
Issue to fix: The CS line is going high before a single clock cycle of data is sent, make CS stay low until all eight bits are sent over
