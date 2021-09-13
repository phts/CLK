function decToBin(x) {
  return x.toString(2).padStart(4, '0').split('').reverse().join('')
}

const CLK_DIGIT_TO_DECODER_VALUE = [3, 2, 7, 4, 1, 9, 8, 0, 5, 6]
const DECODER_VALUE_TO_PIN = [16,15,8,9,13,14,11,10,1,2]
const DECODER_PIN_TO_CONNECTOR_PIN = {
  1: 1,
  2: 2,
  16: 3,
  15: 4,
  14: 5,
  13: 6,
  11: 7,
  10: 8,
  9: 9,
  8: 10,
}
const CONNECTOR_PIN_TO_LAMP_PIN = {
  1: 6,
  2: 7,
  3: 5,
  4: 8,
  5: 4,
  6: 9,
  7: 3,
  8: 10,
  9: 2,
  10: 11,
}
const LAMP_PIN_TO_LAMP_DIGIT = {
  2: 0,
  3: 9,
  4: 8,
  5: 7,
  6: 6,
  7: 5,
  8: 4,
  9: 3,
  10: 2,
  11: 1,
}

const output = [0,1,2,3,4,5,6,7,8,9].map(x =>{
  const decValue = CLK_DIGIT_TO_DECODER_VALUE[x]
  const decoderPin = DECODER_VALUE_TO_PIN[decValue]
  const connectorPin = DECODER_PIN_TO_CONNECTOR_PIN[decoderPin]
  const lampPin = CONNECTOR_PIN_TO_LAMP_PIN[connectorPin]
  return {
    'Clock digit': x,
    'Clock digit (bin)': decToBin(x),
    'Tmp decoder value': decValue,
    'Tmp decoder value (bin)': decToBin(decValue),
    'Decoder pin': decoderPin,
    'Connector pin': connectorPin,
    'Lamp pin': lampPin,
    'Lamp digit': LAMP_PIN_TO_LAMP_DIGIT[lampPin],
  }
})

console.table(output)
