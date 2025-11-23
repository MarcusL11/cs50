<!--markdownlint-disabled-->

# HyperDjangoKit

**Django SaaS E-Commerce Starter Kit**

> **Video Walkthrough**: [Watch the 3-Minute Demo](PLACEHOLDER_VIDEO_URL)

---

## Overview

HyperDjangoKit is a production-ready Django starter kit that combines **subscription-based SaaS** and **e-commerce** functionality into a single, cohesive platform. Built for developers who want to skip the 100+ hours of boilerplate setup and ship their MVP faster, this kit provides everything needed to launch a modern web application with recurring revenue streams.

**What You Get:**

- Multi-tier subscription management with Stripe integration
- Complete e-commerce platform with shopping cart and checkout
- Production-ready authentication with social login (Google OAuth)
- Modern, responsive UI built with Tailwind CSS and DaisyUI
- User dashboard for self-service account and subscription management
- Feature-gating system for tiered access control

---

## Key Features

### 🔐 Authentication & User Management

- **Django Allauth** integration for robust user authentication
- Username and email-based login
- Social authentication (Google OAuth) with easy expansion to other providers
- Email verification flows (configurable)
- Password reset and account recovery
- Session management with activity tracking
- User profile management with avatar uploads

### 💳 Payments & Subscriptions

- **Stripe** integration via **dj-stripe** for seamless payment processing
- Multi-tier subscription plans (Starter, Standard, Premium)
- Monthly and yearly billing options
- Subscription lifecycle management (upgrades, downgrades, cancellations)
- Customer billing portal access
- Webhook handling for real-time payment events
- Invoice generation and history
- Support for both recurring subscriptions and one-time purchases

### 🛒 E-Commerce Platform

- Product catalog with categories and filtering
- Multiple product images with alt text for accessibility
- Shopping basket with quantity management
- Stripe Checkout integration for secure payments
- Order history and tracking
- Receipt generation and download
- Product badges (New, Popular) and sorting options
- Admin interface for product and category management

### 🎨 Modern UI/UX

- **Tailwind CSS 4.x** for utility-first styling
- **DaisyUI 5.x** component library for rapid development
- **Django Cotton** for reusable template components
- Dark mode support with theme switcher
- Responsive design for mobile, tablet, and desktop
- **Datastar** for reactive, HATEOAS-powered interactions without heavy JavaScript frameworks
- Flexoki color scheme for modern, accessible design

### 🏗️ Architecture & Development

- **Django 5.2** with Python 3.13
- **PostgreSQL** database for production-ready data storage
- Modular app architecture for maintainability
- Environment-based configuration with **django-environ**
- Comprehensive admin interface for data management
- Best practices for security, scalability, and code organization

### 🚀 Developer Experience

- Component-based templating with **django-cotton**, **slippers**, and **template-partials**
- Form customization with **django-widget-tweaks**
- Debug toolbar for development
- Clear separation of settings (base, development, production)
- Reusable utilities for payments, notifications, and common operations

---

## Tech Stack

### Core Framework

- **Django 5.2.7** - High-level Python web framework
- **Python 3.13** - Modern Python runtime
- **PostgreSQL** - Relational database (via psycopg2-binary)

### Authentication

- **django-allauth 65.12.1** - Comprehensive authentication solution
- **django-allauth-ui 1.8.1** - Customized authentication UI templates
- **OAuth 2.0** - Social authentication protocol

### Payments

- **dj-stripe 2.10.3** - Django integration for Stripe
- **stripe 13.0.1** - Official Stripe Python SDK

### Frontend & Templates

- **django-cotton 2.1.3** - Component-based template library
- **slippers 0.6.2** - Additional component system
- **django-template-partials 25.2** - Template partials for reusable snippets
- **django-widget-tweaks 1.5.0** - Form widget customization
- **django-tailwind 4.4.1** - Tailwind CSS integration for Django
- **pytailwindcss 0.3.0** - Standalone Tailwind CSS CLI
- **datastar-py 0.6.5** - Server-sent events for reactive UI updates

### UI & Styling

- **Tailwind CSS v4.x** - Utility-first CSS framework
- **DaisyUI v5.x** - Component library built on Tailwind

### Utilities

- **django-environ 0.12.0** - Environment variable management
- **django-cookie-consent 0.9.0** - GDPR cookie consent
- **Pillow 12.0.0** - Image processing and manipulation

### Development

- **django-debug-toolbar** - Development debugging (non-production)

---

## Project Structure

```
django_saas_ecom_starterkit/
├── src/
│   ├── apps/
│   │   ├── accounts/          # Custom user model and authentication
│   │   ├── allauth_ui/        # Customized authentication templates
│   │   ├── core/              # Shared utilities and payment logic
│   │   ├── shop/              # E-commerce products and checkout
│   │   ├── subscriptions/     # SaaS subscription management
│   │   ├── user_dashboard/    # User self-service portal
│   │   └── theme/             # Tailwind CSS and UI theming
│   ├── config/
│   │   ├── settings/          # Django settings (base, dev, prod)
│   │   ├── urls.py            # URL routing configuration
│   │   └── wsgi.py            # WSGI application entry point
│   ├── static/                # Static files (CSS, JS, images)
│   ├── templates/             # Shared templates and components
│   └── manage.py              # Django management script
├── requirements/
│   ├── production.txt         # Production dependencies
│   └── production.in          # Dependency specifications
├── docs/                      # Documentation files
└── README.md                  # This file
```

---

## Django Apps

### **accounts**

Custom user model extending Django's `AbstractUser` with:

- Subscription tracking (cached FK to Stripe subscription)
- Customer reference (FK to Stripe customer object)
- Profile image support
- Feature-gating methods (`has_feature()`, `get_subscription_features()`)

### **allauth_ui**

Customized authentication interface providing:

- Login, signup, and logout forms
- Email verification flows
- Password reset functionality
- Social authentication integration
- Email management interface

### **core**

Shared utilities and base models:

- `BaseModel` abstract class with UUID primary keys and timestamps
- Payment utilities (`get_or_create_customer`, `format_stripe_amount`)
- UI helpers (toast notifications, request detection)
- Common validators and helper functions

### **shop**

Complete e-commerce platform:

- Product catalog with categories
- Shopping basket and cart management
- Stripe Checkout integration
- Order processing and history
- Product images and metadata
- Admin interface for product management

### **subscriptions**

SaaS subscription management:

- Multi-tier pricing plans (Starter, Standard, Premium)
- Feature definitions and access control
- Stripe subscription creation and management
- Billing portal integration
- Webhook handling for subscription events

### **user_dashboard**

Self-service user portal:

- Account profile management
- Email and password management
- Active session tracking
- Subscription management and billing history
- Order history and receipts

### **theme**

UI theming and styling:

- Tailwind CSS integration
- DaisyUI component library
- Dark mode support
- Custom CSS compilation

---

## Subscription Plans & Features

HyperDjangoKit includes three pre-configured subscription tiers:

### Starter Plan

- Unlimited Widgets
- Basic support

### Standard Plan (Most Popular)

- Unlimited Widgets
- Priority Support
- Enhanced features

### Premium Plan

- Unlimited Widgets
- Priority Support
- Ludicrous Mode
- All advanced features

**Feature-Gating System:**

- Features are defined in `apps/subscriptions/features.py`
- Access checked via `user.has_feature('FEATURE_NAME')`
- Plans configured in `apps/subscriptions/metadata.py`
- Automatically synced with Stripe via webhooks

---

## Acknowledgments & Inspiration

This project was built with inspiration and knowledge from the following excellent sources:

- **Theme Design**: [Flexoki](https://stephango.com/flexoki) by Steph Ango - A modern, accessible color scheme
- **Django Education**: [LearnDjango](https://learndjango.com/) by William S. Vincent - Comprehensive Django tutorials and best practices
- **File Structure**: [django-structurator](https://github.com/maulik-0207/django-structurator) - Django project organization patterns
- **SaaS Starter Kit**: [SaaS Pegasus](https://www.saaspegasus.com/) by Cory Zue - Professional SaaS starter kit patterns and best practices

---

## What Makes This Different?

### Dual Revenue Model

Unlike most starter kits that focus solely on subscriptions or e-commerce, HyperDjangoKit supports both:

- Users can subscribe to tiered plans for recurring revenue
- Users can make one-time purchases through the shop
- Both systems work seamlessly together

### HATEOAS-First Approach

Instead of heavy JavaScript frameworks, HyperDjangoKit uses **Datastar** for reactive UI updates:

- Server-driven UI state
- Minimal client-side JavaScript
- Progressive enhancement
- Faster development cycles

### Production-Ready from Day One

- Stripe webhook handling configured
- Environment-based settings
- Security best practices implemented
- Scalable architecture
- Comprehensive error handling

### Component-Based Templates

Modern frontend development patterns with Django:

- Reusable UI components via django-cotton
- Type-safe template rendering
- Minimal template duplication
- Easy to maintain and extend

---

## Use Cases

HyperDjangoKit is perfect for:

- **SaaS Applications**: Launch subscription-based software with tiered pricing
- **Membership Sites**: Offer premium content with recurring payments
- **Digital Product Stores**: Sell courses, templates, or digital goods
- **Hybrid Platforms**: Combine subscriptions with one-time purchases
- **MVPs**: Validate your idea quickly with a production-ready foundation

---

## Getting Started

### Prerequisites

- Python 3.13+
- PostgreSQL
- Stripe account (for payments)
- Node.js (for Tailwind CSS compilation)

### Installation

1. Clone the repository
2. Create a virtual environment
3. Install dependencies: `pip install -r requirements/production.txt`
4. Configure environment variables (database, Stripe keys, etc.)
5. Run migrations: `python manage.py migrate`
6. Create a superuser: `python manage.py createsuperuser`
7. Start the development server: `python manage.py runserver`

### Configuration

- Set up Stripe webhook endpoints
- Configure social authentication providers
- Customize subscription plans and features
- Update branding and theme colors

---

## License

[Add your license information here]

---

## Support

For questions, issues, or feature requests, please [open an issue](https://github.com/your-repo/issues) or contact [your-email@example.com].

---

**Built with ❤️ for developers who want to ship faster**
