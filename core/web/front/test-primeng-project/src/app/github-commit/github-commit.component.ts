import { Component, OnInit } from '@angular/core';
import { CommonModule } from '@angular/common'; 
import { GithubService } from '../services/github.service';

@Component({
  selector: 'app-github-commit',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './github-commit.component.html',
  styleUrls: ['./github-commit.component.css']
})
export class GithubCommitComponent implements OnInit {
  contributions: { [date: string]: number } = {};
  days: string[] = [];

  constructor(private githubService: GithubService) {}

  ngOnInit(): void {
    this.githubService.getCommits().subscribe(data => {
      this.contributions = data;
      this.generateDays();
    });
  }

  generateDays(): void {
    const today = new Date();
    for (let i = 0; i < 90; i++) {
      const date = new Date();
      date.setDate(today.getDate() - i);
      const dateString = date.toISOString().split('T')[0];
      this.days.unshift(dateString);
    }
  }

  getIntensity(date: string): string {
    const count = this.contributions[date] || 0;
    if (count > 10) return '#216e39';
    if (count > 5) return '#30a14e';
    if (count > 2) return '#40c463';
    if (count > 0) return '#9be9a8';
    return '#ebedf0';
  }
}