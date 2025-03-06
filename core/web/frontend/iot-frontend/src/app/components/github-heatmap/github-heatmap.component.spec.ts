import { ComponentFixture, TestBed } from '@angular/core/testing';

import { GithubHeatmapComponent } from './github-heatmap.component';

describe('GithubHeatmapComponent', () => {
  let component: GithubHeatmapComponent;
  let fixture: ComponentFixture<GithubHeatmapComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [GithubHeatmapComponent]
    })
    .compileComponents();

    fixture = TestBed.createComponent(GithubHeatmapComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
