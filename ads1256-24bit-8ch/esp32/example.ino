// Arduino (Arduino-framework) example for ESP32/Uno that uses SPI to talk to the ADS1256, waits for DRDY, and reads all eight single-ended channels converting 24-bit samples to voltages.
//
// Buy this module: https://shillehtek.com/products/ads1256-adc-spi-24-bit-8-channel-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ads1256-adc-spi-24-bit-8-channel-module-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// ADS1256 24-bit ADC - read all eight inputs as single-ended voltages (no library needed)
// Uno/Nano: SCLK = D13, DIN = D11, DOUT = D12, CS = D10, DRDY = D9
// ESP32:    SCLK = GPIO 18, DIN = GPIO 23, DOUT = GPIO 19, CS = GPIO 5, DRDY = GPIO 4
// Both:     5V pin = 5 V, GND = GND, PDWN = 3.3 V
#include <SPI.h>

#if defined(ESP32)
const int PIN_CS = 5;
const int PIN_DRDY = 4;
#else
const int PIN_CS = 10;
const int PIN_DRDY = 9;
#endif

const float VREF = 2.5;              // on-board reference voltage

const uint8_t CMD_WAKEUP  = 0x00;
const uint8_t CMD_RDATA   = 0x01;
const uint8_t CMD_SDATAC  = 0x0F;
const uint8_t CMD_RREG    = 0x10;
const uint8_t CMD_WREG    = 0x50;
const uint8_t CMD_SELFCAL = 0xF0;
const uint8_t CMD_SYNC    = 0xFC;
const uint8_t CMD_RESET   = 0xFE;

const uint8_t REG_STATUS = 0x00;
const uint8_t REG_MUX    = 0x01;
const uint8_t REG_ADCON  = 0x02;
const uint8_t REG_DRATE  = 0x03;

SPISettings adcSPI(1000000, MSBFIRST, SPI_MODE1);   // the chip allows up to 1.92 MHz

// Waits until DRDY goes low. Returns false after one second without a new reading.
bool waitDRDY() {
  unsigned long start = millis();
  while (digitalRead(PIN_DRDY) == HIGH) {
    if (millis() - start > 1000) return false;
  }
  return true;
}

void sendCommand(uint8_t command) {
  SPI.beginTransaction(adcSPI);
  digitalWrite(PIN_CS, LOW);
  SPI.transfer(command);
  digitalWrite(PIN_CS, HIGH);
  SPI.endTransaction();
}

void writeRegister(uint8_t reg, uint8_t value) {
  SPI.beginTransaction(adcSPI);
  digitalWrite(PIN_CS, LOW);
  SPI.transfer(CMD_WREG | reg);
  SPI.transfer(0x00);                // write one register
  SPI.transfer(value);
  digitalWrite(PIN_CS, HIGH);
  SPI.endTransaction();
}

uint8_t readRegister(uint8_t reg) {
  SPI.beginTransaction(adcSPI);
  digitalWrite(PIN_CS, LOW);
  SPI.transfer(CMD_RREG | reg);
  SPI.transfer(0x00);                // read one register
  delayMicroseconds(10);             // the chip needs 6.5 us before it answers
  uint8_t value = SPI.transfer(0x00);
  digitalWrite(PIN_CS, HIGH);
  SPI.endTransaction();
  return value;
}

// Selects AIN<channel> against ground, restarts the filter and returns the settled voltage
float readVolts(uint8_t channel) {
  writeRegister(REG_MUX, (channel << 4) | 0x08);   // positive = AINx, negative = AINCOM

  SPI.beginTransaction(adcSPI);
  digitalWrite(PIN_CS, LOW);
  SPI.transfer(CMD_SYNC);
  delayMicroseconds(5);
  SPI.transfer(CMD_WAKEUP);
  digitalWrite(PIN_CS, HIGH);
  SPI.endTransaction();

  delay(12);                         // one full conversion at 100 samples per second
  waitDRDY();

  SPI.beginTransaction(adcSPI);
  digitalWrite(PIN_CS, LOW);
  SPI.transfer(CMD_RDATA);
  delayMicroseconds(10);             // the chip needs 6.5 us before it answers
  int32_t code = SPI.transfer(0x00);
  code = (code << 8) | SPI.transfer(0x00);
  code = (code << 8) | SPI.transfer(0x00);
  digitalWrite(PIN_CS, HIGH);
  SPI.endTransaction();

  if (code & 0x800000) code -= 0x1000000;       // 24-bit two's complement to signed
  return code * (2.0 * VREF) / 8388607.0;       // gain 1: full scale = +/-5 V
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_CS, OUTPUT);
  digitalWrite(PIN_CS, HIGH);
  pinMode(PIN_DRDY, INPUT);
#if defined(ESP32)
  SPI.begin(18, 19, 23);             // SCLK, DOUT (MISO), DIN (MOSI)
#else
  SPI.begin();
#endif
  delay(50);

  sendCommand(CMD_RESET);
  delay(10);
  sendCommand(CMD_SDATAC);
  delay(1);

  uint8_t id = readRegister(REG_STATUS) >> 4;
  if (id != 3) {
    Serial.print("ADS1256 not found (ID ");
    Serial.print(id);
    Serial.println(") - check wiring, 5 V power and PDWN");
    while (true) { delay(1000); }
  }

  writeRegister(REG_ADCON, 0x00);    // gain 1, clock output off
  writeRegister(REG_DRATE, 0x82);    // 100 samples per second
  sendCommand(CMD_SELFCAL);          // calibrate for these settings
  delay(100);
  waitDRDY();
}

void loop() {
  for (uint8_t channel = 0; channel < 8; channel++) {
    Serial.print("AIN");
    Serial.print(channel);
    Serial.print(": ");
    Serial.print(readVolts(channel), 5);
    Serial.println(" V");
  }
  Serial.println();
  delay(1000);
}
