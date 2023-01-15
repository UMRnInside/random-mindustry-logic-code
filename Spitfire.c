#include <mlogevo/everything.h>
typedef struct MlogObject MlogObj;

void main() {
    double x = 0x0D00, y = 0x0721;
    int shooting = 0;
    int i = 0;
    int playerEngaged = 0;
    do {
        MlogObj turret = getlink(i);
        if (i == 0 && playerEngaged <= 0) {
            x = turret.shootX, y = turret.shootY;
            shooting = turret.shooting;
            playerEngaged = 0;
        } else if (turret.controlled == builtins.ctrlPlayer) {
            x = turret.shootX, y = turret.shootY;
            shooting = turret.shooting;
            playerEngaged = 3;
        } else {
            control_shoot(turret, x, y, shooting);
        }
        i++;
        if (i >= builtins.links) {
            i = 0;
            playerEngaged--;
        }
    } while (1);
}
