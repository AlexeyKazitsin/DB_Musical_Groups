--
-- PostgreSQL database dump
--

-- Dumped from database version 14.7 (Ubuntu 14.7-0ubuntu0.22.04.1)
-- Dumped by pg_dump version 14.7 (Ubuntu 14.7-0ubuntu0.22.04.1)

-- Started on 2023-05-20 20:57:53 MSK

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- TOC entry 214 (class 1259 OID 16552)
-- Name: albums; Type: TABLE; Schema: public; Owner: alexey
--

CREATE TABLE public.albums (
    album_id integer NOT NULL,
    album_name text NOT NULL,
    release_date date
);


ALTER TABLE public.albums OWNER TO alexey;

--
-- TOC entry 213 (class 1259 OID 16551)
-- Name: albums_album_id_seq; Type: SEQUENCE; Schema: public; Owner: alexey
--

CREATE SEQUENCE public.albums_album_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.albums_album_id_seq OWNER TO alexey;

--
-- TOC entry 3422 (class 0 OID 0)
-- Dependencies: 213
-- Name: albums_album_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: alexey
--

ALTER SEQUENCE public.albums_album_id_seq OWNED BY public.albums.album_id;


--
-- TOC entry 212 (class 1259 OID 16538)
-- Name: band_members; Type: TABLE; Schema: public; Owner: alexey
--

CREATE TABLE public.band_members (
    member_id integer NOT NULL,
    full_name text NOT NULL,
    role text,
    age integer,
    band_id integer NOT NULL
);


ALTER TABLE public.band_members OWNER TO alexey;

--
-- TOC entry 211 (class 1259 OID 16537)
-- Name: band_members_member_id_seq; Type: SEQUENCE; Schema: public; Owner: alexey
--

CREATE SEQUENCE public.band_members_member_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.band_members_member_id_seq OWNER TO alexey;

--
-- TOC entry 3423 (class 0 OID 0)
-- Dependencies: 211
-- Name: band_members_member_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: alexey
--

ALTER SEQUENCE public.band_members_member_id_seq OWNED BY public.band_members.member_id;


--
-- TOC entry 210 (class 1259 OID 16529)
-- Name: bands; Type: TABLE; Schema: public; Owner: alexey
--

CREATE TABLE public.bands (
    band_id integer NOT NULL,
    band_name text NOT NULL,
    creation_date date,
    country text,
    members_amount integer NOT NULL,
    genre text
);


ALTER TABLE public.bands OWNER TO alexey;

--
-- TOC entry 209 (class 1259 OID 16528)
-- Name: bands_band_id_seq; Type: SEQUENCE; Schema: public; Owner: alexey
--

CREATE SEQUENCE public.bands_band_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.bands_band_id_seq OWNER TO alexey;

--
-- TOC entry 3424 (class 0 OID 0)
-- Dependencies: 209
-- Name: bands_band_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: alexey
--

ALTER SEQUENCE public.bands_band_id_seq OWNED BY public.bands.band_id;


--
-- TOC entry 216 (class 1259 OID 16561)
-- Name: people; Type: TABLE; Schema: public; Owner: alexey
--

CREATE TABLE public.people (
    person_id integer NOT NULL,
    full_name text NOT NULL,
    age integer NOT NULL
);


ALTER TABLE public.people OWNER TO alexey;

--
-- TOC entry 215 (class 1259 OID 16560)
-- Name: people_person_id_seq; Type: SEQUENCE; Schema: public; Owner: alexey
--

CREATE SEQUENCE public.people_person_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.people_person_id_seq OWNER TO alexey;

--
-- TOC entry 3425 (class 0 OID 0)
-- Dependencies: 215
-- Name: people_person_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: alexey
--

ALTER SEQUENCE public.people_person_id_seq OWNED BY public.people.person_id;


--
-- TOC entry 218 (class 1259 OID 16570)
-- Name: places; Type: TABLE; Schema: public; Owner: alexey
--

CREATE TABLE public.places (
    place_id integer NOT NULL,
    city text NOT NULL,
    address text,
    capacity integer
);


ALTER TABLE public.places OWNER TO alexey;

--
-- TOC entry 217 (class 1259 OID 16569)
-- Name: places_place_id_seq; Type: SEQUENCE; Schema: public; Owner: alexey
--

CREATE SEQUENCE public.places_place_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.places_place_id_seq OWNER TO alexey;

--
-- TOC entry 3426 (class 0 OID 0)
-- Dependencies: 217
-- Name: places_place_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: alexey
--

ALTER SEQUENCE public.places_place_id_seq OWNED BY public.places.place_id;


--
-- TOC entry 220 (class 1259 OID 16579)
-- Name: songs; Type: TABLE; Schema: public; Owner: alexey
--

CREATE TABLE public.songs (
    song_id integer NOT NULL,
    song_name text NOT NULL,
    album_id integer NOT NULL,
    composer_id integer,
    songwriter_id integer,
    band_id integer NOT NULL
);


ALTER TABLE public.songs OWNER TO alexey;

--
-- TOC entry 219 (class 1259 OID 16578)
-- Name: songs_song_id_seq; Type: SEQUENCE; Schema: public; Owner: alexey
--

CREATE SEQUENCE public.songs_song_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.songs_song_id_seq OWNER TO alexey;

--
-- TOC entry 3427 (class 0 OID 0)
-- Dependencies: 219
-- Name: songs_song_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: alexey
--

ALTER SEQUENCE public.songs_song_id_seq OWNED BY public.songs.song_id;


--
-- TOC entry 224 (class 1259 OID 16605)
-- Name: tour_songs; Type: TABLE; Schema: public; Owner: alexey
--

CREATE TABLE public.tour_songs (
    id integer NOT NULL,
    song_id integer NOT NULL,
    tour_id integer NOT NULL
);


ALTER TABLE public.tour_songs OWNER TO alexey;

--
-- TOC entry 223 (class 1259 OID 16604)
-- Name: tour_songs_id_seq; Type: SEQUENCE; Schema: public; Owner: alexey
--

CREATE SEQUENCE public.tour_songs_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.tour_songs_id_seq OWNER TO alexey;

--
-- TOC entry 3428 (class 0 OID 0)
-- Dependencies: 223
-- Name: tour_songs_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: alexey
--

ALTER SEQUENCE public.tour_songs_id_seq OWNED BY public.tour_songs.id;


--
-- TOC entry 222 (class 1259 OID 16588)
-- Name: tours; Type: TABLE; Schema: public; Owner: alexey
--

CREATE TABLE public.tours (
    tour_id integer NOT NULL,
    tour_name text NOT NULL,
    start_time time without time zone,
    end_time time without time zone,
    tour_date date,
    ticket_price money NOT NULL,
    amount_sold_tickets integer,
    band_id integer NOT NULL,
    place_id integer NOT NULL
);


ALTER TABLE public.tours OWNER TO alexey;

--
-- TOC entry 221 (class 1259 OID 16587)
-- Name: tours_tour_id_seq; Type: SEQUENCE; Schema: public; Owner: alexey
--

CREATE SEQUENCE public.tours_tour_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.tours_tour_id_seq OWNER TO alexey;

--
-- TOC entry 3429 (class 0 OID 0)
-- Dependencies: 221
-- Name: tours_tour_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: alexey
--

ALTER SEQUENCE public.tours_tour_id_seq OWNED BY public.tours.tour_id;


--
-- TOC entry 3246 (class 2604 OID 16555)
-- Name: albums album_id; Type: DEFAULT; Schema: public; Owner: alexey
--

ALTER TABLE ONLY public.albums ALTER COLUMN album_id SET DEFAULT nextval('public.albums_album_id_seq'::regclass);


--
-- TOC entry 3245 (class 2604 OID 16541)
-- Name: band_members member_id; Type: DEFAULT; Schema: public; Owner: alexey
--

ALTER TABLE ONLY public.band_members ALTER COLUMN member_id SET DEFAULT nextval('public.band_members_member_id_seq'::regclass);


--
-- TOC entry 3244 (class 2604 OID 16532)
-- Name: bands band_id; Type: DEFAULT; Schema: public; Owner: alexey
--

ALTER TABLE ONLY public.bands ALTER COLUMN band_id SET DEFAULT nextval('public.bands_band_id_seq'::regclass);


--
-- TOC entry 3247 (class 2604 OID 16564)
-- Name: people person_id; Type: DEFAULT; Schema: public; Owner: alexey
--

ALTER TABLE ONLY public.people ALTER COLUMN person_id SET DEFAULT nextval('public.people_person_id_seq'::regclass);


--
-- TOC entry 3248 (class 2604 OID 16573)
-- Name: places place_id; Type: DEFAULT; Schema: public; Owner: alexey
--

ALTER TABLE ONLY public.places ALTER COLUMN place_id SET DEFAULT nextval('public.places_place_id_seq'::regclass);


--
-- TOC entry 3249 (class 2604 OID 16582)
-- Name: songs song_id; Type: DEFAULT; Schema: public; Owner: alexey
--

ALTER TABLE ONLY public.songs ALTER COLUMN song_id SET DEFAULT nextval('public.songs_song_id_seq'::regclass);


--
-- TOC entry 3252 (class 2604 OID 16608)
-- Name: tour_songs id; Type: DEFAULT; Schema: public; Owner: alexey
--

ALTER TABLE ONLY public.tour_songs ALTER COLUMN id SET DEFAULT nextval('public.tour_songs_id_seq'::regclass);


--
-- TOC entry 3250 (class 2604 OID 16591)
-- Name: tours tour_id; Type: DEFAULT; Schema: public; Owner: alexey
--

ALTER TABLE ONLY public.tours ALTER COLUMN tour_id SET DEFAULT nextval('public.tours_tour_id_seq'::regclass);


--
-- TOC entry 3258 (class 2606 OID 16559)
-- Name: albums albums_pkey; Type: CONSTRAINT; Schema: public; Owner: alexey
--

ALTER TABLE ONLY public.albums
    ADD CONSTRAINT albums_pkey PRIMARY KEY (album_id);


--
-- TOC entry 3256 (class 2606 OID 16545)
-- Name: band_members band_members_pkey; Type: CONSTRAINT; Schema: public; Owner: alexey
--

ALTER TABLE ONLY public.band_members
    ADD CONSTRAINT band_members_pkey PRIMARY KEY (member_id);


--
-- TOC entry 3254 (class 2606 OID 16536)
-- Name: bands bands_pkey; Type: CONSTRAINT; Schema: public; Owner: alexey
--

ALTER TABLE ONLY public.bands
    ADD CONSTRAINT bands_pkey PRIMARY KEY (band_id);


--
-- TOC entry 3260 (class 2606 OID 16568)
-- Name: people people_pkey; Type: CONSTRAINT; Schema: public; Owner: alexey
--

ALTER TABLE ONLY public.people
    ADD CONSTRAINT people_pkey PRIMARY KEY (person_id);


--
-- TOC entry 3262 (class 2606 OID 16577)
-- Name: places places_pkey; Type: CONSTRAINT; Schema: public; Owner: alexey
--

ALTER TABLE ONLY public.places
    ADD CONSTRAINT places_pkey PRIMARY KEY (place_id);


--
-- TOC entry 3251 (class 2606 OID 16596)
-- Name: tours price_c; Type: CHECK CONSTRAINT; Schema: public; Owner: alexey
--

ALTER TABLE public.tours
    ADD CONSTRAINT price_c CHECK ((ticket_price > (0)::money)) NOT VALID;


--
-- TOC entry 3264 (class 2606 OID 16586)
-- Name: songs songs_pkey; Type: CONSTRAINT; Schema: public; Owner: alexey
--

ALTER TABLE ONLY public.songs
    ADD CONSTRAINT songs_pkey PRIMARY KEY (song_id);


--
-- TOC entry 3268 (class 2606 OID 16610)
-- Name: tour_songs tour_songs_pkey; Type: CONSTRAINT; Schema: public; Owner: alexey
--

ALTER TABLE ONLY public.tour_songs
    ADD CONSTRAINT tour_songs_pkey PRIMARY KEY (id);


--
-- TOC entry 3266 (class 2606 OID 16595)
-- Name: tours tours_pkey; Type: CONSTRAINT; Schema: public; Owner: alexey
--

ALTER TABLE ONLY public.tours
    ADD CONSTRAINT tours_pkey PRIMARY KEY (tour_id);


--
-- TOC entry 3277 (class 2606 OID 16616)
-- Name: tour_songs FK_song_id; Type: FK CONSTRAINT; Schema: public; Owner: alexey
--

ALTER TABLE ONLY public.tour_songs
    ADD CONSTRAINT "FK_song_id" FOREIGN KEY (song_id) REFERENCES public.songs(song_id);


--
-- TOC entry 3276 (class 2606 OID 16611)
-- Name: tour_songs FK_tour_id; Type: FK CONSTRAINT; Schema: public; Owner: alexey
--

ALTER TABLE ONLY public.tour_songs
    ADD CONSTRAINT "FK_tour_id" FOREIGN KEY (tour_id) REFERENCES public.tours(tour_id);


--
-- TOC entry 3271 (class 2606 OID 16631)
-- Name: songs albums_to_songs; Type: FK CONSTRAINT; Schema: public; Owner: alexey
--

ALTER TABLE ONLY public.songs
    ADD CONSTRAINT albums_to_songs FOREIGN KEY (album_id) REFERENCES public.albums(album_id);


--
-- TOC entry 3269 (class 2606 OID 16546)
-- Name: band_members bands_to_members; Type: FK CONSTRAINT; Schema: public; Owner: alexey
--

ALTER TABLE ONLY public.band_members
    ADD CONSTRAINT bands_to_members FOREIGN KEY (band_id) REFERENCES public.bands(band_id);


--
-- TOC entry 3270 (class 2606 OID 16626)
-- Name: songs bands_to_songs; Type: FK CONSTRAINT; Schema: public; Owner: alexey
--

ALTER TABLE ONLY public.songs
    ADD CONSTRAINT bands_to_songs FOREIGN KEY (band_id) REFERENCES public.bands(band_id);


--
-- TOC entry 3274 (class 2606 OID 16621)
-- Name: tours bands_to_tours; Type: FK CONSTRAINT; Schema: public; Owner: alexey
--

ALTER TABLE ONLY public.tours
    ADD CONSTRAINT bands_to_tours FOREIGN KEY (band_id) REFERENCES public.bands(band_id);


--
-- TOC entry 3272 (class 2606 OID 16641)
-- Name: songs songs_to_composers; Type: FK CONSTRAINT; Schema: public; Owner: alexey
--

ALTER TABLE ONLY public.songs
    ADD CONSTRAINT songs_to_composers FOREIGN KEY (composer_id) REFERENCES public.people(person_id);


--
-- TOC entry 3273 (class 2606 OID 16646)
-- Name: songs songs_to_songwriters; Type: FK CONSTRAINT; Schema: public; Owner: alexey
--

ALTER TABLE ONLY public.songs
    ADD CONSTRAINT songs_to_songwriters FOREIGN KEY (songwriter_id) REFERENCES public.people(person_id);


--
-- TOC entry 3275 (class 2606 OID 16636)
-- Name: tours tours_to_places; Type: FK CONSTRAINT; Schema: public; Owner: alexey
--

ALTER TABLE ONLY public.tours
    ADD CONSTRAINT tours_to_places FOREIGN KEY (place_id) REFERENCES public.places(place_id);


-- Completed on 2023-05-20 20:57:54 MSK

--
-- PostgreSQL database dump complete
--

