import { Injectable,OnInit } from '@angular/core';
import { environment } from '../../environments/environment';
import * as io from 'socket.io-client';
import {Observable} from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class SocketService {

  socket: any;

  constructor() {
      this.socket = io.io(environment.wsUsl);

   }

   webSocketConnect() {
     return this.socket;
   } 

   listen(eventName:string) {
     return new Observable((subscriber)=>{
        this.socket.on(eventName,(data)=>{
          subscriber.next(data);
        })

     });
   }

   emit(eventName:string,data:any) {
     this.socket.emit(eventName,data);
   }

   

}
