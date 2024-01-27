Arduino Nano:

![image](https://github.com/hele5768/Alkoblas/assets/156685745/82b9079a-871a-4d95-b8ca-03a50b734107)

Figur 2: Definierar olika värden och importerar de bibliotek som krävs 

![image](https://github.com/hele5768/Alkoblas/assets/156685745/753c84c9-5898-4274-ab7b-6d5a4a406d60)

Figur 3: Sparar olika bitmaps som bestämmer grafiken som visas upp på skärmen 

![image](https://github.com/hele5768/Alkoblas/assets/156685745/173f1cf0-3e16-419c-834c-296dd778097b)

Figur 4:  Visar batteriindikatorn 

![image](https://github.com/hele5768/Alkoblas/assets/156685745/ebce75b9-a6ad-42ef-8cfb-6819254c841c)

![image](https://github.com/hele5768/Alkoblas/assets/156685745/075a82e9-bff0-48fc-8b08-d8c8710f76ed)

Figur 5:  Funktionen som visar menyn och bestämmer vilket val man är på 

![image](https://github.com/hele5768/Alkoblas/assets/156685745/1172d740-2431-46c3-8121-fbc158235ac5)

Figur 6:  Funktion för mätning 

![image](https://github.com/hele5768/Alkoblas/assets/156685745/975629f2-1fab-4eb3-88c4-f1ec52e8c5d5)

Figur 7:  Funktion som tar emot data från den andra arduino via I2C och wire.h biblioteket 

UNO kod: 


![image](https://github.com/hele5768/Alkoblas/assets/156685745/0b6de435-22da-4b46-9b32-396a965ee704)

Figur 8:  Inkluderar nödvändiga bibliotek och definierar variabler 

![image](https://github.com/hele5768/Alkoblas/assets/156685745/1adef5a6-ccc3-492b-8346-c80c7adc63ca)

Figur 9:  Förbereder högtalaren och SD kort-läsaren 

![image](https://github.com/hele5768/Alkoblas/assets/156685745/f2a5fcf3-7f70-4aee-817d-9fb90b8851cf)

Figur 10:  Denna kod delar en inmatad sträng baserat på en given avgränsare och lagrar de resulterande delarna i en lista 

![image](https://github.com/hele5768/Alkoblas/assets/156685745/42ea4880-0a42-4a33-8dd1-31999c2cbab9)

Figur 11:  Villkorssats som startar mätningen ifall Nano kortet skickar en puls 

![image](https://github.com/hele5768/Alkoblas/assets/156685745/f41746b9-420c-4f82-9bff-03d2d31a0c9a)

Figur 12:  Bestämmer vilka ljudfiler som högtalaren ska spela upp 

![image](https://github.com/hele5768/Alkoblas/assets/156685745/2e123fd5-9300-4a0e-b3fa-b75e4617b605)

Figur 13+14:  Mäthistorik funktionen blir tillkallad i Nano så skickas även en signal till UNO som skickar de värden som ligger i lagringen 
