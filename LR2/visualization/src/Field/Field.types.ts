export enum DwellerType {
  None = 'None',
  Plant = 'Plant',
  Herbivore = 'Herbivore',
  Carnivore = 'Carnivore',
}


interface BaseDweller {
  type: DwellerType
  name: string
  lives: number
  size: number
  minSize: number
  maxSize: number
}

interface Plant extends BaseDweller {
  type: DwellerType.Plant
  minLives: number
  maxLives: number
}

interface BaseAnimal extends BaseDweller {
  sex: 'Male' | 'Female'
  lifetime: number
  maxLifetime: number
  stamina: number
  maxStamina: number
}

export interface Carnivore extends BaseAnimal {
  type: DwellerType.Carnivore
}

export interface Herbivore extends BaseAnimal {
  type: DwellerType.Herbivore
}

export type Animal = Herbivore | Carnivore
export type Dweller = Plant | Animal

export type Square = Dweller[]
