#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include "audio.h"
#include "entidades.h"

void acelera(struct Player *car, ALLEGRO_AUDIO_STREAM *audio)
{
    if(car->marcha==1)
    {
        if(car->giro<100)
        {
            car->giro+=0.001;
            car->volume+=0.001;
        }
        else
        {
            car->marcha++;
            car->giro-=50;
        }
    }

    else if(car->marcha==2)
    {

    }

    else if(car->marcha==3)
    {

    }

    else if(car->marcha==4)
    {

    }

    else if(car->marcha==5)
    {

    }
}
