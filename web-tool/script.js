const pressureEl = document.getElementById('pressure');
const temperatureEl = document.getElementById('temperature');
const batteryEl = document.getElementById('battery');
const logEl = document.getElementById('log');
const connectButton = document.getElementById('connect');

let device;
let characteristicMap = {};

function appendLog(message) {
  const row = document.createElement('div');
  row.textContent = `[${new Date().toLocaleTimeString()}] ${message}`;
  logEl.prepend(row);
}

async function requestDevice() {
  try {
    device = await navigator.bluetooth.requestDevice({
      filters: [{ services: ['e7b01b7f-39b7-4602-8d02-f5b88c7a9b5a'] }],
      optionalServices: ['180f'],
    });
    appendLog(`Selected device: ${device.name}`);
    await connect();
  } catch (error) {
    appendLog(`Connection failed: ${error}`);
  }
}

async function connect() {
  const server = await device.gatt.connect();
  const services = await server.getPrimaryServices();

  for (const service of services) {
    const characteristics = await service.getCharacteristics();
    for (const characteristic of characteristics) {
      characteristicMap[characteristic.uuid] = characteristic;
      if (characteristic.properties.notify) {
        characteristic.addEventListener('characteristicvaluechanged', () => handleUpdate(characteristic));
        await characteristic.startNotifications();
      }
      // Prime UI with initial values when readable
      if (characteristic.properties.read) {
        await handleUpdate(characteristic, true);
      }
    }
  }

  appendLog('Connected and listening for updates');
}

function decodeFloat(dataView) {
  return dataView.getFloat32(0, true);
}

async function handleUpdate(characteristic, isRead = false) {
  const value = isRead ? await characteristic.readValue() : characteristic.value;
  const uuid = characteristic.uuid.toLowerCase();

  if (uuid === '5c68f082-5a7c-4028-a24c-6c6c0ce3c4b2') {
    const pressure = decodeFloat(value);
    pressureEl.textContent = `${pressure.toFixed(2)} bar`;
  } else if (uuid === '3f3b4e6d-7a2a-4c57-94d9-22461c9c4b71') {
    const temperature = decodeFloat(value);
    temperatureEl.textContent = `${temperature.toFixed(1)} °C`;
  } else if (uuid === '2a19') {
    const battery = value.getUint8(0);
    batteryEl.textContent = `${battery}%`;
  } else if (uuid === 'd9e7b13a-6c0c-4c22-8e4a-1e6162b23c53') {
    const decoder = new TextDecoder();
    appendLog(decoder.decode(value.buffer));
  } else {
    appendLog(`Unhandled update from ${uuid}`);
  }
}

connectButton.addEventListener('click', () => {
  if (!navigator.bluetooth) {
    appendLog('Web Bluetooth is not supported in this browser.');
    return;
  }
  requestDevice();
});

appendLog('Ready. Click "Connect via BLE" to start.');
