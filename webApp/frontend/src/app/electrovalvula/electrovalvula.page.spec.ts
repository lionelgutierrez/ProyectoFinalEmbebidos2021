import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { IonicModule } from '@ionic/angular';

import { ElectrovalvulaPage } from './electrovalvula.page';

describe('ElectrovalvulaPage', () => {
  let component: ElectrovalvulaPage;
  let fixture: ComponentFixture<ElectrovalvulaPage>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ ElectrovalvulaPage ],
      imports: [IonicModule.forRoot()]
    }).compileComponents();

    fixture = TestBed.createComponent(ElectrovalvulaPage);
    component = fixture.componentInstance;
    fixture.detectChanges();
  }));

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
