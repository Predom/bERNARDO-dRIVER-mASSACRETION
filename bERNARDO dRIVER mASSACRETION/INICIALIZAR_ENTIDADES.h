    ///player declaração e init
    struct Ponto2D PLAYERMODELSOURCE[4]={{-200,-100},{-200,100},{200,100},{200,-100}};

    struct CONVEXPOLYGON PLAYERMODEL={PLAYERMODELSOURCE, 4};
    struct Ponto2D PLAYERMODELCACHE[4];
    struct Player PLAYER={{&PLAYERMODEL,{PLAYERMODELCACHE,4},0,0,0,0,0,0,0,0,0,10},0,1,1,1};
