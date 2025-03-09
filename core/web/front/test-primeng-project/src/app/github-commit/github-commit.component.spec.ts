import { ComponentFixture, TestBed } from '@angular/core/testing';

import { GithubCommitComponent } from './github-commit.component';

describe('GithubCommitComponent', () => {
  let component: GithubCommitComponent;
  let fixture: ComponentFixture<GithubCommitComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [GithubCommitComponent]
    })
    .compileComponents();

    fixture = TestBed.createComponent(GithubCommitComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
