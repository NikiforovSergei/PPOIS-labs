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
        *field = *newField;
    }

    void mainCycle::eat(gameField::field *field)
    {
        const unsigned int width = field->size().first;
        const unsigned int height = field->size().second;

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
                isAte = false;
            }
        }
        else
            for (auto hunter : animals)
                hunter->starving();
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
                reproductionAnimals(tmpCell);
            }
    }

    void mainCycle::reproductionAnimals(gameField::cell *_cell)
    {
        if (_cell->entityCount() < 4 and
            (_cell->get<animal>().size() >= 2 or _cell->get<grassEater>().size() >= 2))
        {
            gameField::cell tmpCell = *_cell;
            for (auto i : tmpCell.get<animal>())
                for (auto j : tmpCell.get<animal>())
                    if (i->isLovely(j))
                    {
                        _cell->put(new animal(
                            i->getName(), i->getHealth(), i->size(),
                            (sex_t)(random() % 2), 15));
                        tmpCell.del(i);
                        tmpCell.del(j);
                        break;
                    }
            for (auto i : tmpCell.get<grassEater>())
                for (auto j : tmpCell.get<grassEater>())
                    if (i->isLovely(j))
                    {
                        _cell->put(new grassEater(
                            i->getName(), i->getHealth(), i->size(),
                            (sex_t)(random() % 2),
                            (unsigned int)(i->getSpeed() / 2 + j->getSpeed() / 2),
                            (i->getChanceToSurvive() / 2 + j->getChanceToSurvive() / 2)));
                        tmpCell.del(i);
                        tmpCell.del(j);
                        break;
                    }
        }
    }

    void mainCycle::die(gameField::field *field)
    {
        for (int i = 0; i < field->size().second; i++)
            for (int j = 0; j < field->size().first; j++)
            {
                gameField::cell *tmpCell = field->getCell(j, i);
                dieAnimals(tmpCell);
                dieGrassEaters(tmpCell);
                diePlant(tmpCell);
            }
    }

    void mainCycle::dieAnimals(gameField::cell *_cell)
    {
        for (auto i : _cell->get<animal>())
        {
            i->getDamage((int)(i->getHealth() * 1 / 7));
            if (i->isDie())
            {
                delete i;
                _cell->del(i);
            }
        }
    }

    void mainCycle::dieGrassEaters(gameField::cell *_cell)
    {
        for (auto i : _cell->get<grassEater>())
        {
            i->getDamage((int)(i->getHealth() * 1 / 7));
            if (i->isDie())
            {
                delete i;
                _cell->del(i);
            }
        }
    }

    void mainCycle::diePlant(gameField::cell *_cell)
    {
        plant *_plant = _cell->get<plant>();
        if (_plant != nullptr)
            if (_plant->getHealth() <= 0)
            {
                delete _plant;
                _plant = nullptr;
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
