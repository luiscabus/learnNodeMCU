

void helloDisplay(){
  display.clear();
    display.setFont(ArialMT_Plain_16);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
//    display.drawStrings(0, 0, "Olá, identifique-se");
    display.drawStringMaxWidth(0, 0, 128, "Olá, identifique-se");
  display.display();
}

void printthenclearDisplay(String param, int tempo)
{
  display.clear();
    display.setFont(ArialMT_Plain_16);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawString(0, 0, param);
  display.display();
  delay(tempo);
  
  helloDisplay();
  return;
}

