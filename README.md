# apts
Programmējamais uzdevums Recenzenti
Atmiņa: 20 MB
Laiks: 0.5 second
Ievadfails: reviewers.in
Izvadfails: reviewers.out

Apraksts
Žurnāla „All About Science” galvenais redaktors kādu dienu konstatēja, ka rodas problēmas ar visu iesūtīto rakstu kvalitatīvu recenzēšanu. Pēdējos gados zinātne visās jomās attīstās strauji, rakstu ir daudz un attiecīgi ir daudz redakcijai piesaistīto recenzentu. Visu recenzentu pārvaldīšana bez datorizētas sistēmas ir palikusi grūta.

Tika nolemts izveidot elektronisko kartotēku, kas aizstās esošo kartīšu sistēmu. Katram recenzentam ir unikāls vārds, ko veido simbolu {a..z, A..Z, 0..9} virkne garumā [1..100]. Lai būtu lielāka anonimitāte, katram recenzentam ir [1..50] unikālu pseidonīmu. Pseidonīmiem tika izmantoti skaitļi robežās [1..1’000’000’000]. Viens un tas pats pseidonīms dažādiem piesaistītajiem recenzentiem nevar tikt piešķirts, t.i. katrā brīdī pēc kāda no pseidonīmiem var noskaidrot konkrēto recenzentu. Žurnāla redakcija nolēma, ka vienlaicīgi nebūs vairāk kā 10’000 recenzentu.

Tā kā uzskaite līdz šim nebija precīza, tad gadījās, ka vienam recenzentam pseidonīms vecajā kartīšu sistēmā ir minēts vairākas reizes (dublikāti ielikšanas komandā) un informāciju par recenzentu ir jāievada vairākos piegājienos (var būt vairākas ielikšanas komandas piesaistītajam recenzentam). Ielikšanas komandā pseidonīmi nekādā veidā nav sakārtoti, jo pirms ievadīšanas jaunajā sistēmā vecās kartītes netika kārtotas.

Jāizveido elektroniska kartotēka, kas nodrošina recenzentu:

ielikšanu vai tā pseidonīmu saraksta papildināšanu (tiek piesaistīti jauni recenzenti vai jau reģistrētam recenzentam tiek papildināts pseidonīmu saraksts);
izmešanu (notiek atteikšanās no recenzenta pakalpojumiem);
meklēšanu (recenzenta unikālā vārda atrašana, ja zināms kāds no pseidonīmiem).
Pēc recenzenta izņemšanas no kartotēkas jaunajiem recenzentiem atkal var izmantot pseidonīmus, kas bija piekārtoti kādam agrāk piesaistītam recenzentam.

Jūsu uzdevums ir noprogrammēt šīs kartotēkas kodolu, kas visas operācijas veic ļoti ātri ( ~O(log(n)) ).

Ieejā ir fails, kas simulē reālās dzīves notikumus jeb komandas kartotēkai. Katra komanda ar parametriem tiek rakstīta savā rindā. Katrā faila rindā var būt pēc patikas daudz lieki tukšumi. Faila lielums nav ierobežots. Ieejas dati ir korekti saskaņā ar ieejas datu formātu un dotajiem ierobežojumiem.

Ieeja un izeja (kartotēkas komandas un darbība)
Ielikšana vai pseidonīmu saraksta papildināšana
Ieejā rinda formātā:

I name count key_1 ... key_count
I ir saīsinājums no Insert
name ir recenzenta unikālais vārds
count ir pseidonīmu skaits [1..50], kas piekārtoti recenzentam
key_1 ... key_count ir ar tukšumiem atdalīti visi pseidonīmi
Izejā rinda, kas satur:

vārdu “ok”, ja recenzents veiksmīgi ielikts vai esošajam recenzentam iespējams papildināts pseidonīmu saraksts,
ok
vārdu “no”, ja recenzentu nevar ielikt, jo kāds pseidonīms jau ir izmantots kādam citam kartotēkā esošam recenzentam vai arī recenzentam unikālu pseidonīmu skaits pārsniegs 50. Šajā gadījumā nekādas izmaiņas sistēmā netiek veiktas!
no
Recenzenta izmešana
Ieejā rinda formātā:

D key
D ir saīsinājums no Delete
key ir izmetamā recenzenta kāds no pseidonīmiem
Izejā rinda, kas satur:

vārdu “ok”, ja recenzents ir veiksmīgi izmests
ok
vārdu “no”, ja recenzentu nevar izmest, jo nav recenzenta ar norādīto pseidonīmu
no
Recenzenta meklēšana
Ieejā rinda formātā:

L key
L ir saīsinājums no Look_up
key ir meklējamā recenzenta kāds no pseidonīmiem
Izejā rinda, kas satur:

recenzenta vārdu, ja recenzents ir veiksmīgi atrasts,
Name
vārdu “no”, ja recenzentu nevar atrast, jo nav recenzenta ar norādīto pseidonīmu.
no
Piemērs:
Ieejas faila reviewers.in saturs:

I JackSmart 3 9 1009 1000009
L 1000009
I TedPumpkinhead 1 19
I PeterMeter 1 9
L 19
D 19
L 19
I JohnCritic 2 1 19
L 19
L 1
L 9
Izejas faila reviewers.out saturs:

ok
JackSmart
ok
no
TedPumpkinhead
ok
no
ok
JohnCritic
JohnCritic
JackSmart
