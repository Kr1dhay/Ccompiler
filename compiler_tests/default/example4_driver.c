int add_five();


int main() {
    int result = add_five();
    printf("Result from add_five(): %d\n", result);
    return !(result == 5);  // exits with 0 if correct, 1 if wrong
}
