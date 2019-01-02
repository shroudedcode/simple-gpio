declare class SimpleGPIO {
  constructor()

  setupInput(pin: number)
  setupOutput(pin: number)
  read(pin: number): boolean
  write(pin: number, value: boolean): void
}

export = SimpleGPIO
