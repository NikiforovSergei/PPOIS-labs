#include "mainCycle.hpp"
#include "../gameField/fieldAndCell.hpp"

namespace gameCycle
{
    void mainCycle::move(gameField::field *field)
    {
        const int width = field->size().first;
        const int height = field->size().second;
        gameField::cell exampleCell = *field->getCell(0, 0);
        exampleCell.clear();
        gameField::field newField(width, height, exampleCell);

        for (int i = 0; i < width; i++)
            for (int j = 0; j < height; j++)
            {
                gameField::cell *oldCell = field->getCell(i, j);

                if (oldCell->get<plant>())
                    newField.getCell(i, j)->put(oldCell->get<plant>());

                for (animal *k : oldCell->get<animal>())
                {
                    const int moveToX = (k->move().first + i) % width;
                    const int moveToY = (k->move().second + j) % height;
                    int count = 0;
                    while (newField.getCell(moveToX >= 0 ? moveToX : (width + moveToX),
                                            moveToY >= 0 ? moveToY : (height + moveToY))
                               ->put(k) and
                           count < 4)
                    {
                        count++;
                    }
                }

                for (grassEater *k : oldCell->get<grassEater>())
                {
                    const int moveToX = (k->move().first + i + width) % width;
                    const int moveToY = (k->move().second + j + height) % height;
                    int count = 0;
                    while (newField.getCell(moveToX >= 0 ? moveToX : (width + moveToX),
                                            moveToY >= 0 ? moveToY : (height + moveToY))
                               ->put(k) and
                           count < 4)
                    {
                        count++;
                    }
                }
            }
        field->clear();
        *field = newField;
    }

    void mainCycle::eat(gameField::field *field)
    {
        const uint width = field->size().first;
        const uint height = field->size().second;

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
        if (!tmpCell->get<animal>().empty() and !tmpCell->get<grassEater>().empty())
        {
            bool isAte = false;

            for (int i = 0; i < tmpCell->get<animal>().size(); ++i)
            {
                for (int j = 0; j < tmpCell->get<grassEater>().size(); ++j)
                    if (!tmpCell->get<grassEater>().at(j)->isAlive())
                    {
                        delete tmpCell->get<grassEater>().at(j);
                        tmpCell->del(tmpCell->get<grassEater>().at(j));
                        isAte = true;
                        break;
                    }
                    else
                        continue;

                if (!isAte)
                    tmpCell->get<animal>().at(i)->starving();
                else
                    tmpCell->get<animal>().at(i)->saturation();
                isAte = false;
            }
        }
        else
            for (int i = 0; i < tmpCell->get<animal>().size(); ++i)
                tmpCell->get<animal>().at(i)->starving();
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
                else
                    k->starving();
            }
    }

    void mainCycle::reproduction(gameField::field *field)
    {
        for (int i = 0; i < field->size().first; i++)
            for (int j = 0; j < field->size().second; j++)
            {
                gameField::cell *tmpCell = field->getCell(i, j);
                reproductionAnimals(tmpCell);

                if (tmpCell->get<plant>() != nullptr)
                    if (rand() % 10 < 1)
                    {
                        const int moveToX = ((rand() % 3 - 1) + i) % field->size().first;
                        const int moveToY = ((rand() % 3 - 1) + j) % field->size().second;

                        while (field->getCell(moveToX >= 0 ? moveToX : (field->size().first + moveToX),
                                              moveToY >= 0 ? moveToY : (field->size().second + moveToY))
                                   ->put(new plant(*(tmpCell->get<plant>()))))
                            ;
                    }
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
                        sex_t childSex = (sex_t)(random() % 2);
                        _cell->put(new animal(
                            i->getName(),
                            floor((i->getHealth() + j->getHealth()) / 2.),
                            floor((i->size() + j->size()) / 2.),
                            childSex,
                            floor((i->getSpeed() + j->getSpeed()) / 2.),
                            floor((i->getMaxStarve() + j->getMaxStarve()) / 2.),
                            i->getSex() == childSex ? i->getSpritePath() : j->getSpritePath()));
                        tmpCell.del(i);
                        tmpCell.del(j);
                        break;
                    }
            for (auto i : tmpCell.get<grassEater>())
                for (auto j : tmpCell.get<grassEater>())
                    if (i->isLovely(j))
                    {
                        sex_t childSex = (sex_t)(random() % 2);
                        _cell->put(new grassEater(
                            i->getName(),
                            floor((i->getHealth() + j->getHealth()) / 2.),
                            floor((i->size() + j->size()) / 2.),
                            (sex_t)childSex,
                            floor(i->getSpeed() / 2. + j->getSpeed() / 2.),
                            i->getChanceToSurvive() / 2. + j->getChanceToSurvive() / 2.,
                            floor((i->getMaxStarve() + j->getMaxStarve()) / 2.),
                            i->getSex() == childSex ? i->getSpritePath() : j->getSpritePath()));
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
            i->getDamage((int)(i->getMaxHealth() * 1 / 10));
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
            i->getDamage((int)(i->getMaxHealth() * 1 / 10));
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
        {
            _plant->getDamage((int)(_plant->getMaxHealth() * 1 / 30));
            if (_plant->getHealth() <= 0)
            {
                delete _plant;
                _plant = nullptr;
            }
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
