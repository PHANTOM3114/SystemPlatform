import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';
import { map } from 'rxjs/operators';

@Injectable({
  providedIn: 'root'
})
export class GithubService {
  private apiUrl = 'https://api.github.com/repos/PHANTOM3114/SystemPlatform/commits';

  constructor(private http: HttpClient) {}

  getCommits(): Observable<any> {
    return this.http.get<any[]>(this.apiUrl).pipe(
      map(commits => {
        const contributions: { [date: string]: number } = {};
        commits.forEach(commit => {
          const date = commit.commit.author.date.split('T')[0];
          contributions[date] = (contributions[date] || 0) + 1;
        });
        return contributions;
      })
    );
  }
}