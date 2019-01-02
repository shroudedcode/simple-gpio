declare class SimpleGPIO {
  constructor()

  read(pin: number): number
  write(pin: number, value: boolean): void
}

export = SimpleGPIO
