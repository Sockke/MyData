#include "design_model.h"

int main() {
  VGA* wire1 = new VGAWire();
  HDMI* wire2 = new HDMIWire();
  Computer c(wire1);
  c.show();
  Computer c1(new HDMITOVGA(wire2));
  c1.show();
  return 0;
}
