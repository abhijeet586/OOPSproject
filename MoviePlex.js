let movies = [];
let bookings = [];

function addMovie() {
    const title = document.getElementById('title').value;
    const genre = document.getElementById('genre').value;
    const timing = document.getElementById('timing').value;
    const price = document.getElementById('price').value;
    if (title && genre && timing && price) {
        movies.push({
            title,
            genre,
            timing,
            price
        });
        displayMovies();
        alert("Movie added successfully!");
    } else {
        alert("Please fill all movie details.");
    }
}

function displayMovies() {
    const list = document.getElementById('moviesList');
    list.innerHTML = '';
    movies.forEach(movie => {
        list.innerHTML += `<p><strong>${movie.title}</strong> | Genre: ${movie.genre} | Timing: ${movie.timing} | Price: Rs.${movie.price}</p>`;
    });
}

function bookTicket() {
    const title = document.getElementById('bookTitle').value;
    const seatNumber = parseInt(document.getElementById('seatNumber').value);
    const timing = document.getElementById('bookTiming').value;
    const popcorn = document.getElementById('popcorn').value === 'true';
    const movie = movies.find(m => m.title === title && m.timing === timing);
    if (!movie) {
        document.getElementById('bookingResult').innerText = "Movie not found.";
        return;
    }
    const totalPrice = parseFloat(movie.price) + (popcorn ? 89 : 0);
    bookings.push({
        title,
        seatNumber,
        timing,
        popcorn,
        totalPrice
    });
    document.getElementById('bookingResult').innerText = `Booking Successful! Total Price: Rs.${totalPrice}`;
}

function suggestByMood() {
    const mood = document.getElementById('moodInput').value.toLowerCase();
    let genre = "any";
    if (mood === "happy") genre = "comedy";
    else if (mood === "sad") genre = "drama";
    else if (mood === "excited") genre = "action";
    else if (mood === "thoughtful") genre = "documentary";
    else if (mood === "romantic") genre = "romance";
    else if (mood === "scared") genre = "horror";
    else if (mood === "curious") genre = "sci-fi";

    const suggestions = movies.filter(movie => movie.genre.toLowerCase() === genre || genre === "any");
    const output = document.getElementById('suggestedMovies');
    output.innerHTML = '';
    if (suggestions.length > 0) {
        suggestions.forEach(movie => {
            output.innerHTML += `<p><strong>${movie.title}</strong> | Genre: ${movie.genre} | Timing: ${movie.timing}</p>`;
        });
    } else {
        output.innerText = "No suggestions available for your mood right now.";
    }
}

function viewBookings() {
    const bookedList = bookings.map(booking => {
        return `<p><strong>${booking.title}</strong> | Seat: ${booking.seatNumber} | Timing: ${booking.timing} | Popcorn: ${booking.popcorn ? "Yes" : "No"} | Total Price: Rs.${booking.totalPrice}</p>`;
    }).join('');
    if (bookedList) {
        alert(`Your Booked Tickets:\n\n${bookedList}`);
    } else {
        alert("No tickets booked yet.");
    }
}

function toggleAdmin() {
    const adminSection = document.getElementById('adminSection');
    const adminButton = document.getElementById('adminButton');

    // Toggle visibility of the admin section
    if (adminSection.style.display === 'none') {
        adminSection.style.display = 'block';
        adminButton.textContent = 'Hide Admin Section'; // Change button text
    } else {
        adminSection.style.display = 'none';
        adminButton.textContent = 'Admin Section'; // Reset button text
    }
}