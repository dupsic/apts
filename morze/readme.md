Morze
Ierobežojumi
Atmiņa	2MB
Laiks	0.2s
Ievadfails	morse.in
Izvadfails	morse.out
Iesūtīt risinājumu

C++11



Programmējamais uzdevums Morze
Atmiņa: 2 MB
Laiks: 0.2 second
Ievadfails: morse.in
Izvadfails: morse.out

Apraksts
Valsts drošības dienesti, klausoties ēteru, uztvēra kādus ziņojumus, kas izraisīja to interesi. Tie sastāvēja no īsiem un gariem pīkstieniem un nelielām pauzītēm ik pēc brīža. Ziņojumi tika pierakstīti uz papīra – īsie signāli ar punktu ‘.’, garie signāli ar horizontālu svītriņu ‘-‘ un nelielās pauzītes ar vertikālu svīru ‘|’. Jaunie darbinieki ilgi bija nesaprašanā, kas tas tāds ir. Vai tas ir spiegs? Varbūt citplanētieši?

Pēc ilgākām nesekmīgām pūlēm atšifrēt dīvainos ziņojumus viņi pakonsultējās pie pensionētā darbinieka, vai viņam nav nācies ar tādu lietu saskarties. Vecais darbinieks paskatījās uz pierakstiem un gardi nosmējās par jauno paaudzi, kas ir aizrāvusies ar jaunajām IT tehnoloģijām un neko vairs nezina par veco labo Morzes ābeci.

Pēc savas atmiņas viņš tabulā sarakstīja daļu no Morzes simbolu atšifrējumiem:

Burts	Morzes kodējums	Skaitlis vai simbols	Morzes kodējums
A	.-	0	-----
B	-...	1	.----
C	-.-.	2	..---
D	-..	3	...--
E	.	4	....-
F	..-.	5	.....
G	--.	6	-....
H	....	7	--...
I	..	8	---..
J	.---	9	----.
K	-.-	.	.-.-.-
L	.-..	,	--..--
M	--	:	---...
N	-.	?	..--..
O	---	-	-....-
P	.--.	/	-..-.
Q	--.-	Tukšums ‘ ‘	.----.
R	.-.	Simbola beigas	|
S	...		
T	-		
U	..-		
V	...-		
W	.--		
X	-..-		
Y	-.--		
Z	--..	
p.s. Pēc atmiņas restaurētais var nesakrist ar īsto Morzes ābeci ( https://en.wikipedia.org/wiki/Morse_code ), piemēram, simbolu un vārdu pauzes.

Pamēģinājis mazliet atšifrēt tekstu, viņš konstatēja, ka vai nu vājo signālu dēļ vai arī pierakstītāja paviršības dēļ, nav atzīmētas visas pauzes vai to ir pārāk daudz. Bez tam viņš brīdināja, ka pēc atmiņas izveidotā Morzes ābece var būt nepilnīga, t.i. daļu no teksta neizdosies atšifrēt, kamēr netiks atrasta pilna Morzes ābece.

Drošības dienests uzreiz griezās pie LU DF studentiem ar lūgumu uzrakstīt programmu, kas atšifrē ziņojumu. Visus ziņojuma fragmentus, kas atrodas starp divām simbola beigu pauzēm un kas nav atrodami Morzes ābecē, ir jāapzīmē ar ‘!’. Liekās pauzes ir jāignorē. Ja teksta beigās nav pauzes, tad pēdējais fragments ir neatpazīstams.

Ieeja
Failā ir tikai viena rinda, kas var būt ļoti gara (līdz 1 MB) un kas sastāv tikai no simboliem ‘.’, ‘-‘ un ‘|’.

Izeja
Atbilstoši ieejas failam rezultātā ir viena rinda, kas satur atšifrējumu atbilstoši uzdevuma Morzes ābecei. Neatšifrētie fragmenti tiek apzīmēti ar simbolu ‘!’.

Piemērs:
Ieejas faila morse.in saturs:

...|---|...|.----.|-....-|.----.|--.|.-..|.-|-...|..|.|-|.----.|--|..-|...|..-|.----.|-..|...-|.|...|.|.-..|.|...|.-.-.-|
Izejas faila morse.out saturs:

SOS – GLABIET MUSU DVESELES.