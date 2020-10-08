#include <SPI.h>
#include "context.h"

void setup()
{
  Serial.begin(9600);
  Serial.println("[setup]: Hello Board!");
  const auto context = Context::getContext();
  if (!context)
  {
    Serial.print("Failed to create Context, abort!");
    return;
  }
  Serial.println("[setup]: context->setup()!");
  context->setup();
  Serial.print("Setup Completes!");
}

void loop()
{
  const auto context = Context::getContext();
  context->executeLoop();
}