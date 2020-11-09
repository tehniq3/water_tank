
/*
 Automat incarcare rezervor 1000L Apa
 - conceptie George DACIN
 - implementare soft: Nicu FLORICA (niq_ro)

 
Citirea nivelului se face prin 3 electrozi conectati la 2,3,4 si inca unul pe fundul bazinului care e pus la gnd 
output se face cu 10,11,12 si 13 cu cate un led de stare pentru fiecare iar pe 13 conectez un releu
___________________________________________________
Daca nivelul e sus,(pin2) atunci pe 12 aprinde led verde
----------------------------------------------------
Daca nivelul e la mijloc, pe 11 aprinde un led galben SI NEAPARAT inchide un releu pana cand starea de 
sus e atinsa, caz in care aprinde 12 si opreste releul si ledul galben
----------------------------------------------------------------------------------------------------------
Daca nivelul e la minim, pe 10 aprinde led rosu si  din nou, inchide releul pana ajunge in starea de sus, 
cand aprinde verdele de pe 12 si releul se opreste
----------------------------------------------------------------------------------------------------------
*/

 
int Plin = 2; // definim pinii pentru electrozi
int Mijloc = 3;
int Gol = 4;
int Releu = 13;
int LedRosu = 10;
int LedGalben = 11;
int LedVerde = 12;

// Asta teoretic ruleaza o data pana se apasa reset:
void setup() {
  // initializam comunicatia seriala
  Serial.begin(9600);
  // pana la realizare voi folosi push butoane pentru test:
  pinMode(Plin, INPUT);
  pinMode(Mijloc, INPUT);
  pinMode(Gol, INPUT);
  pinMode(Releu, OUTPUT);
  pinMode(LedVerde, OUTPUT);
  pinMode(LedGalben, OUTPUT);
  pinMode(LedRosu, OUTPUT);  
  digitalWrite(Plin, HIGH);
  digitalWrite(Mijloc, HIGH);
  digitalWrite(Gol, HIGH);  
  digitalWrite(Releu, LOW);  // pompa oprita
  digitalWrite(LedVerde, LOW);  // led verde stins
  digitalWrite(LedGalben, LOW);  // led galben stins
  digitalWrite(LedRosu, LOW);    // led rosu stins
}

// Asta teoretic ruleaza mereu
void loop() {

if (digitalRead(Plin) == LOW) // rezervor plin
  {
  Serial.println("Apa la maxim -- Cantitate = 1000 Litri ");
  digitalWrite(Releu, LOW);  // pompa se opreste
  digitalWrite(LedVerde, HIGH);  // led verde aprins
  digitalWrite(LedGalben, LOW);  // led galben stins
  digitalWrite(LedRosu, LOW);    // led rosu stins
  }
else  // daca rezervorul nu e plin
{
if (digitalRead(Mijloc)== LOW)
{
    digitalWrite(LedVerde, LOW);  // led verde stins
    digitalWrite(LedGalben, HIGH);  // led galben aprins
    digitalWrite(LedRosu, LOW);    // led rosu stins  
}
else
{
if (digitalRead(Gol)== LOW)  // daca  scazut nivelul sub jumate
  {
    Serial.println("Apa sub jumatate= 500 Litri "); 
    digitalWrite(Releu, HIGH);  // pompa porneste
    digitalWrite(LedVerde, LOW);  // led verde stins
    digitalWrite(LedGalben, HIGH);  // led galben aprins
    digitalWrite(LedRosu, LOW);    // led rosu stins
  }
if (digitalRead(Gol)== HIGH)  // daca nivelul e sub minim
  {
    Serial.println("Rezervor gol"); 
    digitalWrite(Releu, HIGH);  // pompa porneste (iar)
    digitalWrite(LedVerde, LOW);  // led verde stins
    digitalWrite(LedGalben, LOW);  // led galben stinss
    digitalWrite(LedRosu, HIGH);    // led rosu aprins
  }
}
}


} // sfarsit program principal
