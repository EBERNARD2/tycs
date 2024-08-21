package main

import (
	"log"
	"os"
	"gopl.io/ch4/github"
	"html/template"
	"net/http"
)

var mainTempl = template.Must(template.New("issueList").Parse(`
<h1>{{.TotalCount}} issues</h1>
<table>
<tr style='text-align: left'>
	<th>#</th>
	<th>State</th>
	<th>User</th>
	<th>Title</th>
</tr>
{{range.Items}}
<tr>
	<td><a href='{{.HTMLURL}}'>{{.Number}}</a></td>
	<td>State</td>
	<td><a href='{{.User.HTMLURL}}'>{{.User.Login}}</a></td>
	<td><a href='{{.HTMLURL}}'>{{.Title}}</a></td>
</tr>
{{end}}
</table>
`))z

func main() {
	result, err := github.SearchIssues(os.Args[1:])

	if err != nil {
		log.Fatal(err)
	}

	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		if mainTempl.Execute(w, result); err != nil {
			log.Fatal(err)
		}
	})

	log.Fatal(http.ListenAndServe("localhost:8000", nil))
}