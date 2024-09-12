package url

type Values map[string][]string

func (v Values) Get(key string) string {
	if vs := v[key]; len(vs) > 0 {
		return vs[0]
	}

	return ""
}

func (v values) Add(key, value string) {
	v[key] = append(v[key], value)
}