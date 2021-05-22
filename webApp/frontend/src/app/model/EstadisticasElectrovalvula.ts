export class EstadisticasElectrovalvula {

    private _estado: string;
    private _fecha: string;

    public get estado(): string {
        return this.estado;
    }
    public set estado(value: string) {
        this.estado = value;
    }

    public get fecha(): string {
        return this._fecha;
    }
    public set fecha(value: string) {
        this._fecha = value;
    }
    constructor(estado:string, fecha:string) {
        this._estado = estado;
        this._fecha = fecha;
    }
}