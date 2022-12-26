import { Square } from "./Field.types"

let ws: WebSocket
let currentSetField: React.Dispatch<React.SetStateAction<Square[][]>>
let currentRows: number = 0
let currentColumns: number = 0

const connect = (setField: React.Dispatch<React.SetStateAction<Square[][]>>) => {
  if (ws && ws.readyState !== ws.CLOSED) return;
  
  currentSetField = setField
  ws = new WebSocket('ws://192.168.1.108:8080')

  ws.onopen = () => {
    console.log('Connected!')
  }

  ws.onclose = () => {
    console.log('Connection closed.')
  }

  ws.onmessage = ({data}) => {
    const message = JSON.parse(data);
    if (message.mutation === 'update') {
      const field: Square[][] = []
      for (let x = 0; x < currentRows; x++) {
        field.push([])
        for (let y = 0; y < currentColumns; y++) {
          field[x].push(message.payload?.at(x)?.at(y) ?? [])
        }
      }
      setField(field)
    }
  }

  return () => {
    if (ws.readyState === ws.OPEN) {
      ws.close()
    }
  }
}

const init = (rows: number, columns: number) => {
  currentRows = rows
  currentColumns = columns
  ws.send(JSON.stringify({
    action: 'init',
    payload: { rows, columns }
  }))
}

const play = () => {
  ws.send(JSON.stringify({
    action: 'play',
    payload: {}
  }))
}

const reconnect = () => {
  if (currentSetField) {
    if (ws.readyState === ws.OPEN || ws.readyState === ws.CONNECTING) {
      const _onclose = ws.onclose?.bind(ws)
      ws.onclose = (e) => {
        if (_onclose) _onclose(e)
        connect(currentSetField);
      }
      ws.close();
    } else {
      connect(currentSetField);
    }
  }
}


const connection = { connect, reconnect, init, play }

export default connection