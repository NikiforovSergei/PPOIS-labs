#include "mainCycle.hpp"
#include "../gameField/fieldAndCell.hpp"

namespace gameCycle
{
    void mainCycle::move(gameField::field *field)
    {
        const unsigned int width = field->size().first;
        const unsigned int height = field->size().second;
        gameField::field *newField = new gameField::field(width, height);

        for (unsigned int i = 0; i < height; i++)
            for (unsigned int j = 0; j < width; j++)
            {
                gameField::cell *oldCell = field->getCell(j, i);

                for (auto k : oldCell->get<animal>())
                    while (newField->getCell((k->move().first + j + width) % width,
                                             (k->move().second + i + height) % height)
                               ->put(k))
                        ;

                for (auto k : oldCell->get<grassEater>())
                    while (newField->getCell((k->move().first + j + width) % width,
                                             (k->move().second + i + height) % height)
                               ->put(k))
                        ;
            }
        if (field != nullptr)
            delete field;
        field = newField;
    }

    void mainCycle::eat(gameField::field *field)
    {
        const unsigned int width = field->size().first;
        const unsigned int height = field->size().second;
        gameField::field *newField = new gameField::field(width, height);

        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
            {
                gameField::cell *tmpCell = field->getCell(j, i);

                eatPlants(tmpCell);

                eatGrassEaters(tmpCell);
            }
    }

    void mainCycle::eatGrassEaters(gameField::cell *tmpCell)
    {
        std::vector<animal *> animals = tmpCell->get<animal>();
        std::vector<grassEater *> grassEaters = tmpCell->get<grassEater>();
        if (!animals.empty() and !grassEaters.empty())
        {
            bool isAte = false;

            for (auto hunter : animals)
            {
                for (auto victim : grassEaters)
                    if (!victim->isAlive())
                    {
                        delete victim;
                        tmpCell->del(victim);
                        isAte = true;
                        break;
                    }
                    else
                        continue;

                if (!isAte)
                    hunter->starving();
                else
                    hunter->saturation();
            }
        }
    }

    void mainCycle::eatPlants(gameField::cell *tmpCell)
    {
        plant *_plant = tmpCell->get<plant>();

        for (auto k : tmpCell->get<grassEater>())
            if (_plant != nullptr)
            {
                _plant->getDamage(k->size());
                k->saturation();
                if (_plant->isDie())
                {
                    delete _plant;
                    tmpCell->del(_plant);
                    break;
                }
                else if (k->isDie())
                {
                    delete k;
                    tmpCell->del(k);
                }
                else
                    k->starving();
            }
    }

    void mainCycle::reproduction(gameField::field *field)
    {
        for (int i = 0; i < field->size().second; i++)
            for (int j = 0; j < field->size().first; j++)
            {
                gameField::cell *tmpCell = field->getCell(j, i);
            }
    }

    void mainCycle::die(gameField::field *field)
    {
        for (int i = 0; i < field->size().second; i++)
            for (int j = 0; j < field->size().first; j++)
            {
                gameField::cell *tmpCell = field->getCell(j, i);
            }
    }

    void mainCycle::nextStep(gameField::field *field)
    {
        move(field);
        eat(field);
        reproduction(field);
        die(field);
    }
} // namespace gameCycle
