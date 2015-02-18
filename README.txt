EGC - Tema 1
Geometry Dash
Dinu Marian-Alexandru 334 CC

1.Cerinta

Am avut de implementat un joc 2D folosind figuri geometrice simple.
Player-ul era un patrat cu ochi si gura, iar obstacolele erau
triunghiuri si dreptunghiuri. Cercurile faceau ca player-ul sa sara
automat.

2. Utilizare

Space = saritura
ESC = inchiderea ferestrei de joc

3. Implementare
IDE - VS 2012
Compilator - GCC 4.5.2
SO - Windows 8.1

5. Probleme aparute
Am incercat de nenumarate ori sa fac jucatorul sa se roteasca in jurul
centrului sau, dar nu am reusit. Se misca sub forma unei elipse, ceea ce 
ma duce cu gandul la faptul ca  nu calculez bine punctele unde ar trebui sa-l
translatez. Inainte sa incerc translatarea pe Ox merge totul perfect, dupa aceea
nu am mai reusit.

6. Continutul arhivei
Am pornit de la Framework-ul din laboratorul 1 si 2 si
am adaugat cod in main + intr-o clasa creata de mine: Player.
In Player sunt figurile care creeaza fata + metode gen jump() si
collision_detector();

7. Functionalitati
Functionalitati Standard (ca in enunt):
Tot, mai putin rotatia player-ului, care nu mi-a iesit.
Functionalitati Bonus:
Muzica de fundal.
