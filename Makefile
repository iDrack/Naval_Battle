# all : généralement la première du fichier, elle regroupe dans ces dépendances l'ensemble des exécutables à produire.
all : executable

#	cible : dependance
#		commandes

# On cherche à créer le fichier exécutable "executable".
# Pour faire notre exécutable, il fait fonction.o et main.o. Pour cela on fait la commande juste en dessous.
executable: fonction.o main.o
	gcc fonction.o main.o -o executable 
	make -s clean

# Deux cas se présentent ici, ci-dessous plus bas : 
# Soit le fichier fonction.c est plus récent que le fichier fonction.o, la commande est alors exécutée et fonction.o est construit, 
# Soit fonction.o est plus récent que fonction.c est la commande n'est pas exécutée.

# Pour créer le fichier fonction.o, il nous faut le fonction.c ..
fonction.o: fonction.c
	gcc -c fonction.c -o fonction.o

# Idem pour le main.o :
main.o: main.c fonction.h
	gcc -c main.c -o main.o

# clean : elle permet de supprimer tout les fichiers intermédiaires.
clean:
	rm -rf *.o

# mrproper : elle supprime tout ce qui peut être régénéré et permet une reconstruction complète du projet.
mrproper: clean
	rm -rf executable