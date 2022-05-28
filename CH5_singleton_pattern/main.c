static t_data init_data() {}

t_data* get_data() {
	static t_data data = init_data();
	return &data;
}
