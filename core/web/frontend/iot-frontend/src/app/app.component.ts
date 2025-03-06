import { Component, OnInit } from '@angular/core';
import { NavigationComponent } from './components/navigation/navigation.component';
import { DashboardComponent } from './components/dashboard/dashboard.component';
import { GithubHeatmapComponent } from './components/github-heatmap/github-heatmap.component'; 

@Component({
  selector: 'app-root',
  standalone: true,
  imports: [NavigationComponent, DashboardComponent, GithubHeatmapComponent],
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  title = 'iot-frontend';
}