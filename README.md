# UDP_Rrjeta_Kompjuterike

### Kerkesat

``` Server ```

- Të vendosen variabla te cilat përmbajnë numrin e portit (numri i portit të jetë i çfarëdoshëm) dhe IP adresën.

- Të jetë në gjendje të dëgjojë (listen) të paktën të gjithë anëtaret e grupit.

- Të pranojë kërkesat e pajisjeve që dërgojnë request (ku secili anëtarë i grupit duhet te e ekzekutoje të paktën një kërkesë në server).

- Të jetë në gjendje të lexoje mesazhet që dërgohen nga klientët.

- Të jetë në gjendje të jap qasje të plotë të paktën njërit klient për qasje ne folderat/ përmbajtjen në file-t në server.

``` Client ```
 
- Të krijohet socket lidhja me server.

- Njeri nga pajisjet (klientët) të ketë privilegjet write(), read(), execute().

- Klientët tjerë të kenë vetëm read() permission.

- Të behet lidhja me serverin duke përcaktuar sakt portin dhe IP Adresën e serverit.

- Të definohen sakte socket e serverit dhe lidhje të mos dështojë.

- Të jetë në gjendje të lexojë përgjigjet që i kthehen nga serveri.

- Të dërgojë mesazh serverit si në formë tekstit.

- Të ketë qasje të plotë në folderat/ përmbajtjen në server.




Modulet shtese te cilat i ofron Serveri perfshijne:
 1. Append - e cila nuk i mbishkruan contents te nje file, por i shton ne fund te file.
 2. Magic Number Game - e cila i lejon klientit te luaj nje loje te Magic Game Number. Serveri gjeneron nje numer te rastesishem ne rangun 1-100, dhe klienti i ka 5 perpjekje per te gjetur numrin e duhur. Pas seciles perpjekje, serveri i jep informate klientit se a eshte numri qe ka dhene me i madh, apo me i vogel se numri i rastesishem i gjeneruar nga serveri.

Te dy keto module lejohen vetem per klientin i cili i pari ka bere ndonje kerkese ne server. Klientet e tjere kane casje vetem per READ ne files te serverit ose komunikim te thjeshte klient-server.
