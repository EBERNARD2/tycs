package main


import (
	"flag"
)

func scan(path string) {
	print("scan")
}

func stats(email string) {
	print("stats")
}

func main() {
	var folder string
	var email string
	flag.StringVar(&folder, "add", "", "add a new folder to scan for Git repositories")
	flag.StringVar(&email, "email", "your@email.com", "the email to scan")
	flag.Parse()

	if folder != "" {
		scan(folder)
		return
	}

	stats(email)
}


func scan(folder string) {
	fmt.Printf("Found folders:\n\n")
	repositories := recursiveScanFolders(folder)
	filePath := getDotFilePath()
	addNewSliceElementstoFile(filePath, repositories)
	fmt.Printf("\n\nSuccessfully added\n\n")
}