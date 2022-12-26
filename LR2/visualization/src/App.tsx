import React, { useEffect, useState } from 'react'
import s from './App.module.scss'
import connection from './Field/connection'
import { Field } from './Field/Field'
import { Square } from './Field/Field.types'

function App() {
  const [field, setField] = useState<Square[][]>([])
  const [rows, setRows] = useState<number>(3)
  const [columns, setColumns] = useState<number>(2)
  const [speed, setSpeed] = useState<number>(500)
  const [playTimer, setPlayTimer] = useState<NodeJS.Timer>()

  useEffect(() => {
    return connection.connect(setField)
  }, [])

  const play = () => {
    if (playTimer) {
      clearInterval(playTimer)
      setPlayTimer(undefined)
      return
    }
    setPlayTimer(
      setInterval(() => {
        connection.play()
      }, speed)
    )
  }

  return (
    <div className={s.app}>
      <div className={s.toolbar}>
        <button onClick={() => connection.reconnect()}>Reconnect</button>
        <input
          type='number'
          value={rows || ''}
          onChange={(e) => setRows(+e.target.value)}
        />
        <input
          type='number'
          value={columns || ''}
          onChange={(e) => setColumns(+e.target.value)}
        />
        <button onClick={() => connection.init(rows, columns)}>Init</button>
        <input
          type='number'
          step='50'
          value={speed || ''}
          onChange={(e) => setSpeed(+e.target.value)}
        />
        <button onClick={play}>{playTimer ? 'Stop' : 'Play'}</button>
        <button onClick={() => connection.play()}>Step</button>
      </div>
      <Field {...{ field }} />
    </div>
  )
}

export default App
