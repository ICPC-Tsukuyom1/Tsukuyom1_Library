ld dot(Vector A, Vector B) {
    return A.x * B.x + A.y * B.y;
}
ld cross(Vector A, Vector B) {
    return A.x * B.y - A.y * B.x;
}
