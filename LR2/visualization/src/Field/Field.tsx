import React, { useEffect, useState } from 'react'
import s from './Field.module.scss'
import { Dweller, DwellerType, Square } from './Field.types'

const getLevel = (dweller: Dweller) => {
  if (dweller.type === DwellerType.Plant) {
    return dweller.lives / dweller.maxLives
  } else {
  return dweller.lifetime / dweller.maxLifetime
  }
}

const getSize = (dweller: Dweller) => {
  return (
    (dweller.size - dweller.minSize) / (dweller.maxSize - dweller.minSize)
  )
}

const isFemale = (dweller: Dweller) => {
  if (dweller.type !== DwellerType.Plant) {
    if (dweller.sex === 'Female') return ''
  }
}

const getStamina = (dweller: Dweller) => {
  if (dweller.type !== DwellerType.Plant) {
    return Math.max(dweller.stamina / dweller.maxStamina, 0);
  }
}

export const Field = React.memo((props: { field: Square[][] }) => {
  const [squareSize, setSquareSize] = useState(0)
  useEffect(() => {
    const onresize = () => {
      setSquareSize(
        props.field[0]?.length
          ? Math.min(
              (window.innerHeight * 0.8) / props.field[0]?.length,
              (window.innerWidth * 0.9) / props.field.length
            )
          : 0
      )
    }
    onresize()
    window.addEventListener('resize', onresize)
    return () => {
      window.removeEventListener('resize', onresize)
    }
  }, [props.field, setSquareSize])

  return (
    <div className={s.field} style={{ '--square': `${squareSize}px` } as any}>
      {props.field?.map((row, x) => (
        <div key={x}>
          {row.map((square, y) => (
            <div key={y} className={s.square}>
              {square?.map((dweller, z) => (
                <div
                  key={z}
                  className={s.dweller}
                  style={
                    {
                      '--level': getLevel(dweller),
                      '--size': getSize(dweller),
                      '--stamina': getStamina(dweller),
                    } as any
                  }
                  data-type={dweller.type}
                  data-female={isFemale(dweller)}
                />
              ))}
            </div>
          ))}
        </div>
      ))}
    </div>
  )
})
