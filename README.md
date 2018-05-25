# Gestionnaire de réseaux de neurones

## Présentation
Le but de l'application est de permettre créer et utiliser des réseaux de neurones de simplement. Les formats soutenues par l'application comme images a traiter sont le BMP et l'IDX.   

## Compilation
GTK2 est necessaire a la compilation du projet, le package a installer est libgtk2.0-dev.   
   
La compilation s'effectue simplement en utilisant le Makefile fourni :   

> make   
   
compilera le programme et créera un exécutable. 

## Utilisation
> make run  
   
permettra de lancer l'executable  
   
Pour plus de détails, consulter le manuel d'utilisation.  

## Apprentissage
Lors de l'apprentissage le programme ira dans le répertoire spécifié par l'utilisateur pour y chercher des exemples d'apprentissages, tout fichier traité ou non conforme aux formats soutenus sera supprimé.  
   
Les fichiers BMP devront suivre le convention de nomage suivant : etiquette%identifacateur.bmp   
   
ou etiquette correspond a la signifaction de l'image et identificateur etant simplement la pour permettre d'avoir plusieurs images ayant le même signifcation dans un même répertoire   
   
Les fichier IDX devront également respecter une convention de nomage :    
   
  pour les fichier contenant les image : nom.idx3-ubyte   
     
  pour les fichier contenant les etiquettes : nom.idx1-ubyte   
     
Afin de lier le fichier contenant les étiquettes a celui contenant les images, les deux fichier doivent posseder le même nom.   
