/**
 *
 * send to arduino for display
 *
 *
 *
 */


// SerialPort communication ofer USB
const SerialPort = require('serialport');

// get settings
const settings = require('../../settings').ledout;

let buf = new Int8Array(32*8).fill(0);

// setup SerialPort with Arduino std
const port = new SerialPort(
  settings.USBPort,
  {
    baudRate: 250000,
    databits: 8,
    stopBits: 1,
    parity: 'even',
    autoOpen: true,
  }
);

// on "start" message, send led color from buffer
port.on('data', function () {
  port.write(buf);
});

const dgram = require('dgram');
const server = dgram.createSocket('udp4');

server.on('error', (err) => {
  console.error(err);
  throw err;
});

server.on('message', (msg, rinfo) => {
  if(rinfo.size == (settings.colors_per_leds * settings.leds_x * settings.leds_y)){
    buf = msg;
  }
});

server.bind(settings.intern_listen_port);
