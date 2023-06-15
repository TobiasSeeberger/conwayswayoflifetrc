# conwayswayoflifetrc
git add conway.c
git commit
git push
git pull
Compelierbefehl
cl65 -t c64 -o conway.prg conway.c


1. & 2. commit: In diesen zwei commits, haben wir die Anfangsdateien eingefüllt, dass jeder von unseren Gruppe am selben Dokument arbeitet und nicht an verschiedenen. Github ist uns auch eine Hilfe zum Dokumentieren unserer Arbeitsschritte, da wir zurückverfolgen können, was wir alles gemacht haben. 

3. commit: Der dritte commit war ein reiner Bugfix, da in zaehlLebende in einer Zeile eine Klammer gefehlt hat. Diese wurde eingefügt.

4. commit: Hier wurde die README.md erstellt um die benötigten Befehle an die Gruppe zu verteilen.

5. commit: Der fünfte commit war der erste commit, der an der Ablaufszeit des Programmes etwas verändert hat. Hier haben wir die Variable ROUNDS auf 1 gesetzt, damit wir nicht jedes mal das Programm manuell stoppen mussten. Hier haben wir erkannt, dass die Methode initSpielfeld keine wirkliche Funktion hat, außer das Programm zu verlangsamen, da unser Startfeld namens array auf ein weiteres array unter dem Namen spielfeld geladen wurde, konnten wir das umgehen in dem wir das Startfeld direkt unter dem Namen spielfeld erstellt haben. Etwas weiteres was wir entfernt haben, waren unnötige Anzeigen in der while schleife. Dort haben wir 2 gotoxy Befehle entfernt und 2 cprintf Befehle, da die keine Auswirkung auf die Spielregeln hatte und auch keine Funktion, die benötigt wird.

6. commit: Hatte genau das gleiche wie der 4. commit. Wurde doppelt gemacht weil wir die README.md Datei nicht in unseren Ordner bekommen haben. Wir haben ebenfalls entdeckt, dass beim compilieren ebenfalls Optimierungen möglich waren. Das einzige was nötig war, ist nach dem c64 in unserem Compilierbefehl ein -Oirs einfügen mussten. Dadurch verschnellerte sich unser Programm um Einiges.

7. commit: wir haben herausgefunden, dass in zaehlLebende einige *7 versteckt waren, die entfernt werden konnten ohne, dass sich die Funktion des Programms verändert hat. In diesem commit hat sich auch ein Fehler in pruefeRegeln eingeschlichen. wir haben die Funktion des Programms dadurch eingeschränkt, was uns zu diesem Zeitpunkt nicht aufgefallen ist. Dadurch wurde die Zeit sehr stark verkürzt.

8. commit: Hier ist uns unser Fehler aufgefallen und wir haben diesen Behoben, in dem wir pruefeRegeln wieder auf den Originalzustand zurückgesetzt haben. Ebenfalls haben wir in zaehlLebende die Funktion vereinfacht, da uns ein paar unnötige if abfragen aufgefallen sind.

9. commit: Im 9. commit haben wir die Funktion pruefeRegeln in das Hauptprogramm eingefügt, um unnötige Funktionsaufrufe zu eliminieren. Hier haben wir den exakten Code aus der Funktion genommen und ins Hauptprogramm anstatt dem Funktionsaufruf eingefügt. Die Zeit die bei diesem commit dazu geschrieben wurde stimmt nicht, da sich jemand verschrieben hat. Die wirkliche Zeit war 22 s.

10. commit: in diesem commit wurden ein paar Variablen vom datentyp int auf den datentyp register unsigned und register unsigned char geändert. Dadurch gab es eine leichte verschnellerung des Programms.

11. commit: Dieser commit befindet sich nicht mehr in dem main branch, sonder in dem master branch, da wir ein paar Schwierigkeiten mit Github hatten und im Internet nach Lösungen geforscht haben. Deshalb sind ab diesem commit alle weiteren commits im master branch. Hier haben wir das Programm nach int Datentypen abgesucht und jeden int Datentyp durch einen char ersetzt. Diese befanden sich in verschiedenen Funktionen und sind durch das ganze Programm vorhanden.

12. commit: Im 12. commit haben wir die Funktion zaehlLebende vereinfacht, da uns aufgefallen ist, dass for schleifen sehr langsam sind. Das haben wir so gemacht, dass wir für jedes der 9 Felder das überprüft werden soll, den Wert, also ob sich ein Lebendes Element dort befindet, in die Variable lebende gespeichert.

13. commit: Im nächsten schritt haben wir diese Funktion genommen und in das Hauptprogramm verfrachtet, um den Funktionsaufruf zu eliminieren. Danach haben wir die gesamte Funktion aus dem Code gelöscht, um keine Funktion zu erstellen, die nie Aufgerufen wird.

14. commit: Zuerst haben wir einen Fehler behoben, weil wir vergessen haben, die Zahl der Lebenden zurückzusetzen, was die Funktion des gesamten Spieles kaputt machte. Hier haben wir auch die ROUNDS wieder auf 100 gesetzt, um besser erkennen zu können, ob das Programm noch funktioniert.

15. commit: In diesem commit haben wir alle restlichen char Datentypen gesucht und diese durch register unsigned / signed char Datentypen ersetzt. Das haben wir gemacht, weil wir bemerkt haben, dass die meisten char Datentypen kaum genutzt werdern und dadurch das Programm verlangsamt haben.

16. commit: Dieser commit hat sehr viele Zeilen zu dem Programm hizugefügt, da uns aufgefallen ist, dass wir noch for Schleifen vorhanden hatten, welche auch ausprogrammiert werden können, da das schneller ist. Hier haben wir für jeden Wert dieser for Schleifen den Inhalt der for Schleife angepasst und ausgeschrieben.

17. commit: Dieser commit ist der gleiche wie der 15. commit. Wir wissen nicht genau warum es den vorherige commit nicht übernommen hat, deshalb wird er ein zweites mal durchgeführt.

18. commit: Hier wollten wir das gleiche machen wie im 16. commit, da die gleichen for Schleifen mehrmals im Programm waren, aber wenn wir alles ausprogrammiert haben, konnten wir das Programm nicht mehr compilieren und haben es darum sein lassen.

19. commit: Bei diesem Schritt hatten wir hilfe von anderen Mitschülern, da wir nicht viel mehr Ahnung gehabt haben, wie wir noch schneller werden können. Diese Mitschüler haben uns erklärt was wir machen könnten, was wir schlussendlich auch umgesetzt haben. Wir haben die findNachbarn Funktion stark vereinfacht und mit zaehlLebende im Hauptprogramm zusammengeführt, dass wir dann unter den 6s gelandet sind. Dieser Schritt hat den größten Unterschied gemacht. Ebenfalls haben wir den start der clock wieder an den Anfang des Hauptprogrammes gesetzt, da uns mitgeteilt wurde, dass wir diesen am Anfang lassen sollten und nicht vor die while Schleife verschieben.

20. commit: Im 20. und letzten commit haben wir noch die Idee vom 18. commit leicht geändert, in dem wir nur eine der zwei for Schleifen ausprogrammiert haben, was das Programm nocht compilierbar machte. Hier sind wir zu einem Endpunkt gekommen mit einer Zeit von 4.8s für den ersten Durchlauf.

21. commit: fertige README.md Datei hinaufgeladen.