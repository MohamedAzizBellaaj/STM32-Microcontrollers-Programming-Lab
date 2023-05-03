#include <stdint.h>

#define Reg_Enable_RCC (uint32_t *)0x40021018    // adresse du registre assurant l'activation des horloges (RCC) des ports A et C
#define Reg_Config_Led (uint32_t *)0x40011004    // adresse du registre de configuration du Port C (relié aux leds)
#define Reg_BSRR_Led (uint32_t *)0x40011010      // adresses du registre permettant la mise à 1 des bits du port C
#define Reg_BRR_Led (uint32_t *)0x40011014       // adresses du registre permettant la mise à 0 des bits du port C
#define Reg_Config_Bouton (uint32_t *)0x40010800 // adresse du registre de configuration du port A (relié au bouton)
#define Reg_Bouton (uint32_t *)0x40010808        // adresse du registre en entr�e (IDR) du port A

int etat_bouton; // variable permettant de lire l'état du bouton

int main()
{
  // activer les horloges des ports reliés aux leds et au bouton
  *Reg_Enable_RCC |= 0x14;

  // Configurer les bits reliés aux leds
  *Reg_Config_Led &= ~((uint32_t)0xff);
  *Reg_Config_Led |= 0x11;
  // configurer le bit relié au bouton
  *Reg_Config_Bouton &= ~((uint32_t)0xf); // Input Floating
  *Reg_Config_Bouton |= 0x4;

  // Tester Bouton et allumer si appuyé sinon éteindre
  while (1)
  {
    etat_bouton = *Reg_Bouton & 0x1; // lire l'état du bit relié au bouton (bit PA0)
    if (etat_bouton == 0x1)          // si appui
    {
      *Reg_BSRR_Led = 0x3 << 8; // allumer leds
    }
    else // sinon
    {
      // Eteindre les deux leds.
      *Reg_BRR_Led = 0x3 << 8;
    }
  }
}
