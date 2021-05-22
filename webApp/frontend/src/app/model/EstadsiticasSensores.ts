export class EstadsiticasSensores {

    private _temperatura: number;
    private _humedad: number;
    private _fecha: string;

    public get humedad(): number {
        return this.humedad;
    }
    public set humedad(value: number) {
        this.humedad = value;
    }
    public get temperatura(): number {
        return this.temperatura;
    }
    public set temperatura(value: number) {
        this.temperatura = value;
    }

    public get fecha(): string {
        return this._fecha;
    }
    public set fecha(value: string) {
        this._fecha = value;
    }
    constructor(humedad:number, temperatura:number, fecha:string) {
        this._humedad =  humedad;
        this._temperatura = temperatura;
        this._fecha = fecha;
    }
}