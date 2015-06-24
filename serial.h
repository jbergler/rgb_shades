void setup_serial() {
  Serial.begin(9600);
  Serial.setTimeout(25);
}

void loop_serial() {
  if (!Serial || !Serial.available()) return;
  String input = Serial.readStringUntil('\n');
  String result = process_command(input);
  Serial.println(result);
}