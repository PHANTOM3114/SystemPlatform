import { Component } from '@angular/core';
import { NavigationComponent } from './navigation/navigation.component';
import { RouterModule } from '@angular/router';
import { GithubCommitComponent } from './github-commit/github-commit.component';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css'],
  standalone: true,
  imports: [NavigationComponent, RouterModule, GithubCommitComponent],
})
export class AppComponent {
  title = 'test-primeng-project';
}