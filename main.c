#include "produits.h"
#include "categories.h"
#include "utilisateurs.h"
#include "utils.h"
#include "ventes.h"
#include "rapports.h"
#include "menus.h"
#include "init.h"


#include <stdio.h>
#include <stdlib.h>



int main()
{
    initialiserUtilisateurs();
    menuPrincipal();
    return 0;
}


